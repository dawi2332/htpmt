/*
 * Copyright (c) 2008 David Winter (dawi2332@gmail.com)
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

/* $Id$ */

char* program_name;

#include "system.h"
#include "error.h"
#include "basic-auth.h"
#include "fileio.h"
#include "readpasswd.h"

void usage(void);
void version(void);

int
main(int argc, char *argv[])
{
	program_name = argv[0];

	char *secret = NULL;
	char *filename;
	char *username;
	char *password;
	char *ptr;
	char buf[MAX_STRING_LEN];
	char buf1[MAX_STRING_LEN];
	char c;

	static struct
	{
		int	verbose;
		int	version;
		int	help;
		int	to_stdout;
		int	from_cmdline;
		int	force_apr1;
		int	force_crypt;
		int	force_plain;
		int	force_sha1;
		int	delete;
		int	create;
		int	warn;
		int	from_stdin;
		int	verify;
	} flags =
	{
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1
	};

	const struct option options[] =
	{
		{"create",	no_argument,	NULL,		'c'},
		{"to-stdout",	no_argument,	NULL,		'n'},
		{"force-md5", 	no_argument,	NULL,		'm'},
		{"force-crypt",	no_argument,	NULL,		'd'},
		{"force-plain",	no_argument,	NULL,		'p'},
		{"force-sha",	no_argument,	NULL,		's'},
		{"batch-mode",no_argument,	NULL,		'b'},
		{"delete",	no_argument,	NULL,		'D'},
		{"from-stdin",	no_argument,	NULL,		'i'},
		{"help",	no_argument,	&flags.help,	1},
		{"version",	no_argument,	&flags.version,	1},
		{"no-warnings",	no_argument,	&flags.warn, 0},
		{"no-verify",	no_argument,	&flags.verify, 0},
		{NULL,		0,		NULL,		0}
	};

	while ((c = getopt_long(argc, argv, "cnmdpsbDi", options, NULL)) != -1)
	{
		switch (c)
		{
			case 'c':
				flags.create = 1;
				flags.to_stdout = 0;
				break;
			case 'n':
				flags.to_stdout = 1;
				flags.create = 0;
				break;
			case 'm':
				flags.force_apr1 = 1;
				flags.force_crypt = flags.force_sha1 = flags.force_plain = 0;
				break;
			case 'd':
				flags.force_crypt = 1;
				flags.force_apr1 = flags.force_sha1 = flags.force_plain = 0;
				break;
			case 'p':
				flags.force_plain = 1;
				flags.force_apr1 = flags.force_sha1 = flags.force_crypt = 0;
				break;
			case 's':
				flags.force_sha1 = 1;
				flags.force_apr1 = flags.force_plain = flags.force_crypt = 0;
				break;
			case 'b':
				flags.from_cmdline = 1;
				break;
			case 'i':
				flags.from_stdin = 1;
				break;
			case 'D':
				flags.delete = 1;
				break;
			case 'v':
				flags.verbose = 1;
				break;
			case 0:
				break;
			default:
				usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (flags.version)
		version();

	if (flags.help)
		usage();

	if (flags.delete)
	{
		if (argc < 2)
			syntax("you must specify a file and a username");
		delete_from_file(filename, username, NULL);
		exit(EXIT_SUCCESS);
	}

	if (!flags.to_stdout)
	{
		if (argc < 2)
			syntax("you must specify a file and a username");
		if (flags.from_cmdline && argc < 3) 
			syntax("you must specify a file, a username and a password");
		else
			password = argv[2];

		filename = argv[0];
		username = argv[1];
	}
	else
	{
		if (argc < 1)
			syntax("you must specify a username");
		if (flags.from_cmdline && argc < 2)
			syntax("you must specify a username and a password");
		else
			password = argv[1];

		username = argv[0];
	}
	
	if (strlen(username) > MAX_STRING_LEN-1)
		error(EXIT_OVERFLOW, "the username must not contain more than %i characters", MAX_STRING_LEN);

	if (strchr(username, ':') != NULL)
		error(EXIT_ILLEGALCHARS, "\
the username must not contain the character ':'");

	if (flags.force_plain && flags.warn)
		warn("\
the use of the `-p' option is discouraged since anybody with\n\
access to the password file can read (and possibly abuse) it. Use only when\n\
REALLY needed.\n");

	if (flags.force_crypt && flags.warn)
		warn("\
using the `-d' option may require truncating the password to\n\
eight characters\n");

	if (flags.from_cmdline && flags.warn)
		warn("\
the use of the `-b' option is discouraged since the unencrypted\n\
password will be visible on the command line and in the process table.\n");

	if (!flags.from_cmdline && !flags.from_stdin)
	{
		password = readpasswd("Password:", buf, MAX_STRING_LEN, F_NOECHO);
		if (flags.verify)
		{
		       	password = readpasswd("Verify password:", buf1, MAX_STRING_LEN, F_NOECHO);
			if (strncmp(buf, buf1, MAX_STRING_LEN) != 0)
			{
				memset(buf, 0, MAX_STRING_LEN);
				error(EXIT_VERIFICATION, "password mismatch");
			}
		}
	}

	if (flags.from_stdin)
		password = readpasswd("", buf, MAX_STRING_LEN, 0);

	if (strlen(password) > MAX_STRING_LEN-1)
		error(EXIT_OVERFLOW, "the password must not contain more than %i characters", MAX_STRING_LEN-1);

	if (flags.force_plain)
		secret = password;
	if (flags.force_crypt)
		secret = basic_crypt(username, NULL, password, NULL);
	if (flags.force_sha1)
		secret = basic_sha1(username, NULL, password, NULL);
	if (flags.force_apr1)
		secret = basic_apr1(username, NULL, password, NULL);

	if (!flags.to_stdout)
	{
		if (flags.create)
			create_file(filename, username, NULL, secret);
		else
			update_file(filename, username, NULL, secret);
	}
	else
		printf("%s:%s\n", username, secret);

	/* zero everything */
	memset(password, 0, sizeof(password));
	memset(buf, 0, sizeof(buf));
	memset(username, 0, sizeof(username));
	memset(secret, 0, sizeof(secret));

	return EXIT_SUCCESS;
}


void
usage(void)
{
	printf("Usage: %s [OPTIONS]... [FILE] USERNAME [PASSWORD]\n", program_name);
	printf("\n\
Options:\n\n\
  -c, --create                create FILE; overwrite FILE if it exists\n\
  -n, --to-stdout             write data to STDOUT instead of FILE\n\
  -m, --force-md5             force MD5 encryption of the password\n\
  -d, --force-crypt           force crypt() encryption of the password\n\
  -s, --force-sha             force SHA-1 encryption of the password\n\
  -p, --force-plain           don't encrypt password \n\
  -b, --batch-mode            batch mode: use PASSWORD as password instead of\n\
                              prompting for it\n\
  -D, --delete                delete USERNAME from FILE\n\
  -i, --from-stdin            read the password from STDIN instead of\n\
                              prompting for it\n\
  --no-warnings               don't display warnings\n\
  --no-verify                 don't verify passwords when prompting\n\
  --version                   prints version\n\
  --help                      prints this brief help\n");
	printf("\n\
Report bugs at http://code.google.com/p/htpmt/\n");

	exit(EXIT_SUCCESS);
}

void
version(void)
{
	printf("%s - %s %s\n", program_name, PACKAGE_NAME, PACKAGE_VERSION);
	printf("\
Copyright (c) 2008 David Winter (dawi2332@gmail.com). All rights reserved.\n\
This is open source software, see the source for copying conditions.\n");
	exit(EXIT_SUCCESS);
}
