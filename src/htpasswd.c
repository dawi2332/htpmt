/*
 * Copyright 2008-2014 David Winter
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include "basic-auth.h"
#include "fileio.h"
#include "openssl-version.h"
#include "progname.h"
#include "readpasswd.h"
#include "syntax.h"
#include "system.h"

#include <stdbool.h>

void usage(void);
void version(void);

typedef enum { CRYPT, PLAIN, SHA1, APR1 } algo_e;

typedef enum {
  HELP_OPTION,
  VERSION_OPTION,
  NO_WARNINGS_OPTION,
  NO_VERIFY_OPTION
} option_e;

typedef enum { CREATE_MODE, UPDATE_MODE, DELETE_MODE, STDOUT_MODE } mode_e;

typedef enum { STDIN_INPUT, ARGS_INPUT, TTY_INPUT } input_e;

int main(int argc, char *argv[]) {
  char *secret = NULL;
  char *filename;
  char *username;
  char *password;
  char *ptr;
  char buf[MAX_STRING_LEN];
  char buf1[MAX_STRING_LEN];
  char c;

  bool verbose = false;
  bool warn = true;
  bool verify = true;
  mode_e mode = UPDATE_MODE;
  algo_e force_algo = APR1;
  input_e input = TTY_INPUT;

  const struct option options[] = {
      {"create", no_argument, NULL, 'c'},
      {"to-stdout", no_argument, NULL, 'n'},
      {"force-md5", no_argument, NULL, 'm'},
      {"force-crypt", no_argument, NULL, 'd'},
      {"force-plain", no_argument, NULL, 'p'},
      {"force-sha", no_argument, NULL, 's'},
      {"batch-mode", no_argument, NULL, 'b'},
      {"delete", no_argument, NULL, 'D'},
      {"from-stdin", no_argument, NULL, 'i'},
      {"help", no_argument, NULL, HELP_OPTION},
      {"version", no_argument, NULL, VERSION_OPTION},
      {"no-warnings", no_argument, NULL, NO_WARNINGS_OPTION},
      {"no-verify", no_argument, NULL, NO_VERIFY_OPTION},
      {NULL, 0, NULL, 0}};

  setprogname(argv[0]);

  while ((c = getopt_long(argc, argv, "cnmdpsbDi", options, NULL)) != -1) {
    switch (c) {
      case 'c':
        mode = CREATE_MODE;
        break;
      case 'n':
        mode = STDOUT_MODE;
        break;
      case 'm':
        force_algo = APR1;
        break;
      case 'd':
        force_algo = CRYPT;
        break;
      case 'p':
        force_algo = PLAIN;
        break;
      case 's':
        force_algo = SHA1;
        break;
      case 'b':
        input = ARGS_INPUT;
        break;
      case 'i':
        input = STDIN_INPUT;
        break;
      case 'D':
        mode = DELETE_MODE;
        break;
      case 'v':
        verbose = true;
        break;
      case VERSION_OPTION:
        version();
        break;
      case HELP_OPTION:
        usage();
        break;
      case NO_WARNINGS_OPTION:
        warn = false;
        break;
      case NO_VERIFY_OPTION:
        verify = false;
      default:
        usage();
    }
  }

  argc -= optind;
  argv += optind;

  if (mode != STDOUT_MODE) {
    if (argc < 2) {
      syntax("you must specify a file and a username");
    }
    if (input == ARGS_INPUT && argc < 3) {
      syntax("you must specify a file, a username and a password");
    } else {
      password = argv[2];
    }

    filename = argv[0];
    username = argv[1];
  } else {
    if (argc < 1) {
      syntax("you must specify a username");
    }
    if (input == ARGS_INPUT && argc < 2) {
      syntax("you must specify a username and a password");
    } else {
      password = argv[1];
    }

    username = argv[0];
  }

  if (strlen(username) > MAX_STRING_LEN - 1)
    errx(EXIT_OVERFLOW, "the username must not contain more than %i characters",
         MAX_STRING_LEN - 1);

  if (strchr(username, ':') != NULL)
    errx(EXIT_ILLEGALCHARS, "the username must not contain the character ':'");

  if (mode == DELETE_MODE) {
    if (argc < 2) {
      syntax("you must specify a file and a username");
    };

    delete_from_file(filename, username, NULL);
    exit(EXIT_SUCCESS);
  }

  switch (input) {
    case TTY_INPUT:
      password = readpasswd("Password:", buf, MAX_STRING_LEN, F_NOECHO);
      if (verify) {
        password =
            readpasswd("Verify password:", buf1, MAX_STRING_LEN, F_NOECHO);
        if (strncmp(buf, buf1, MAX_STRING_LEN) != 0) {
          memset(buf, 0, MAX_STRING_LEN);
          errx(EXIT_VERIFICATION, "password mismatch");
        }
      }
      break;
    case STDIN_INPUT:
      password = readpasswd("", buf, MAX_STRING_LEN, 0);
      break;
    case ARGS_INPUT:
      if (warn) {
        warnx(
            "the use of the `-b' option is discouraged since the unencrypted "
            "password will be visible on the command line and in the process "
            "table.");
      }
      break;
  }

  if (strlen(password) > MAX_STRING_LEN - 1) {
    errx(EXIT_OVERFLOW, "the password must not contain more than %i characters",
         MAX_STRING_LEN - 1);
  }

  switch (force_algo) {
    case PLAIN:
      if (warn) {
        warnx(
            "the use of the `-p' option is discouraged since anybody with "
            "access to the password file can read (and possibly abuse) it. Use "
            "only when REALLY needed.");
      }
      secret = password;
      break;
    case CRYPT:
      if (warn) {
        warnx(
            "using the `-d' option may require truncating the password to "
            "eight characters.");
      }
      secret = basic_crypt(username, NULL, password, NULL);
      break;
    case SHA1:
      secret = basic_sha1(username, NULL, password, NULL);
      break;
    case APR1:
      secret = basic_apr1(username, NULL, password, NULL);
      break;
  }

  if (strlen(secret) + strlen(username) + 1 > MAX_STRING_LEN - 1) {
    errx(EXIT_OVERFLOW, "resultant user record must not exceed %i characters",
         MAX_STRING_LEN - 1);
  }

  switch (mode) {
    case STDOUT_MODE:
      printf("%s:%s\n", username, secret);
      break;
    case CREATE_MODE:
      create_file(filename, username, NULL, secret);
      break;
    case UPDATE_MODE:
      update_file(filename, username, NULL, secret);
      break;
    default:
      break;
  }

  /* zero everything */
  memset(password, 0, MAX_STRING_LEN);
  memset(buf, 0, sizeof(buf));
  memset(username, 0, MAX_STRING_LEN);
  memset(secret, 0, strlen(secret));

  return EXIT_SUCCESS;
}

void usage(void) {
  printf("Usage: %s [OPTIONS]... [FILE] USERNAME [PASSWORD]\n", getprogname());
  printf(
      "\nOptions:\n"
      "  -c, --create                create FILE; overwrite FILE if it exists\n"
      "  -n, --to-stdout             write data to STDOUT instead of FILE\n"
      "  -m, --force-md5             force MD5 encryption of the password\n"
      "  -d, --force-crypt           force crypt() encryption of the password\n"
      "  -s, --force-sha             force SHA-1 encryption of the password\n"
      "  -p, --force-plain           don't encrypt password \n"
      "  -b, --batch-mode            batch mode: use PASSWORD as password "
      "instead of\n"
      "                              prompting for it\n"
      "  -D, --delete                delete USERNAME from FILE\n"
      "  -i, --from-stdin            read the password from STDIN instead of\n"
      "                              prompting for it\n"
      "  --no-warnings               don't display warnings\n"
      "  --no-verify                 don't verify passwords when prompting\n"
      "  --version                   prints version\n"
      "  --help                      prints this brief help\n\n"
      "Report bugs at http://code.google.com/p/htpmt/\n");
  exit(EXIT_SUCCESS);
}

void version(void) {
  printf("%s - %s %s %s\n", getprogname(), PACKAGE_NAME, VERSION_LONG,
         OPENSSL_VERSION);
  printf(
      "Copyright 2008-2014 David Winter. All rights reserved.\n"
      "This is open source software, see the source for copying conditions.\n");
  exit(EXIT_SUCCESS);
}
