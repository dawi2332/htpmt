/*
 * Copyright 2008-2017 David Winter
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

#include "digest-auth.h"
#include "fileio.h"
#include "openssl-version.h"
#include "progname.h"
#include "readpasswd.h"
#include "syntax.h"
#include "system.h"

void usage(void);
void version(void);

typedef enum {
  HELP_OPTION,
  VERSION_OPTION,
  NO_WARNINGS_OPTION,
  NO_VERIFY_OPTION
} option_enum;

typedef enum { CREATE_MODE, UPDATE_MODE, DELETE_MODE, STDOUT_MODE } mode_enum;

typedef enum { STDIN_INPUT, TTY_INPUT } input_enum;

int main(int argc, char *argv[]) {
  char *secret = NULL;
  char *filename;
  char *username;
  char *password;
  char *realm;
  char *ptr;
  char buf[MAX_STRING_LEN];
  char buf1[MAX_STRING_LEN];
  char c;

  bool verify = true;
  mode_enum mode = UPDATE_MODE;
  input_enum input = TTY_INPUT;

  const struct option options[] = {
      {"create", no_argument, NULL, 'c'},
      {"to-stdout", no_argument, NULL, 'n'},
      {"delete", no_argument, NULL, 'D'},
      {"from-stdin", no_argument, NULL, 'i'},
      {"help", no_argument, NULL, HELP_OPTION},
      {"version", no_argument, NULL, VERSION_OPTION},
      {"no-verify", no_argument, NULL, NO_VERIFY_OPTION},
      {NULL, 0, NULL, 0}};

  setprogname(argv[0]);

  while ((c = getopt_long(argc, argv, "cnDi", options, NULL)) != -1) {
    switch (c) {
      case 'c':
        mode = CREATE_MODE;
        break;
      case 'n':
        mode = STDOUT_MODE;
        break;
      case 'i':
        input = STDIN_INPUT;
        break;
      case 'D':
        mode = DELETE_MODE;
        break;
      case VERSION_OPTION:
        version();
        break;
      case HELP_OPTION:
        usage();
        break;
      case NO_VERIFY_OPTION:
        verify = false;
        break;
      default:
        usage();
        break;
    }
  }
  argc -= optind;
  argv += optind;

  if (mode != STDOUT_MODE) {
    if (argc < 3) syntax("you must specify a file, a realm and a username");

    filename = argv[0];
    realm = argv[1];
    username = argv[2];
  } else {
    if (argc < 2) syntax("you must specify a username and a realm");

    realm = argv[0];
    username = argv[1];
  }

  if (strlen(username) > MAX_STRING_LEN - 1)
    errx(EXIT_OVERFLOW, "the username must not contain more than %i characters",
         MAX_STRING_LEN - 1);

  if (strchr(username, ':') != NULL)
    errx(EXIT_ILLEGALCHARS, "the username must not contain the character ':'");

  if (strlen(realm) > MAX_STRING_LEN - 1)
    errx(EXIT_OVERFLOW, "the realm must not contain more than %i characters",
         MAX_STRING_LEN - 1);

  if (strchr(realm, ':') != NULL)
    errx(EXIT_ILLEGALCHARS, "the realm must not contain the character ':'");

  if (mode == DELETE_MODE) {
    if (argc < 3) syntax("you must specify a file, a realm and a username");
    delete_from_file(filename, username, realm);
    exit(EXIT_SUCCESS);
  }

  switch (input) {
    case TTY_INPUT:
      password = readpasswd("Password:", buf, MAX_STRING_LEN, false);
      if (verify) {
        password = readpasswd("Verify password:", buf1, MAX_STRING_LEN, false);
        if (strncmp(buf, buf1, MAX_STRING_LEN) != 0) {
          memset(buf, 0, MAX_STRING_LEN);
          memset(buf1, 0, MAX_STRING_LEN);
          errx(EXIT_VERIFICATION, "password mismatch");
        }
      }
      break;
    case STDIN_INPUT:
      password = readpasswd("", buf, MAX_STRING_LEN, true);
      break;
  }

  if (strlen(password) > MAX_STRING_LEN - 1)
    errx(EXIT_OVERFLOW, "the password must not contain more than %i characters",
         MAX_STRING_LEN - 1);

  secret = digest_md5(username, realm, password, NULL);

  if (strlen(secret) + strlen(username) + 1 > MAX_STRING_LEN - 1)
    errx(EXIT_OVERFLOW, "resultant user record must not exceed %i characters",
         MAX_STRING_LEN - 1);

  switch (mode) {
    case CREATE_MODE:
      create_file(filename, username, realm, secret);
      break;
    case UPDATE_MODE:
      update_file(filename, username, realm, secret);
      break;
    case STDOUT_MODE:
      printf("%s:%s\n", username, secret);
      break;
    default:
      break;
  }

  /* zero everything */
  memset(buf, 0, sizeof(buf));
  memset(buf1, 0, sizeof(buf1));
  memset(password, 0, MAX_STRING_LEN);
  memset(username, 0, MAX_STRING_LEN);
  memset(realm, 0, sizeof(username));
  memset(secret, 0, strlen(secret));

  return EXIT_SUCCESS;
}

void usage(void) {
  printf("Usage: %s [OPTIONS]... [FILE] REALM USERNAME\n", getprogname());
  printf(
      "\nOptions:\n\n"
      "  -c, --create                create FILE; overwrite FILE if it exists\n"
      "  -n, --to-stdout             write data to STDOUT instead of FILE\n"
      "  -D, --delete                delete USERNAME from FILE\n"
      "  -i, --from-stdin            read the password from STDIN instead of\n"
      "                              prompting for it\n"
      "  --no-verify                 don't verify passwords when prompting\n"
      "  --version                   prints version\n"
      "  --help                      prints this brief help\n"
      "\nReport bugs at http://code.google.com/p/htpmt/\n");
  exit(EXIT_SUCCESS);
}

void version(void) {
  printf("%s - %s %s %s\n", getprogname(), PACKAGE_NAME, VERSION_LONG,
         OPENSSL_VERSION);
  printf(
      "Copyright 2008-2017 David Winter. All rights reserved.\n"
      "This is open source software, see the source for copying conditions.\n");
  exit(EXIT_SUCCESS);
}
