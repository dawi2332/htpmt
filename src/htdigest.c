/*
 * Copyright 2008, 2009, 2010, 2011, 2012 David Winter
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

#include "system.h"
#include "version.h"
#include "version-openssl.h"
#include "digest-auth.h"
#include "fileio.h"
#include "readpasswd.h"
#include "progname.h"

void usage(void);
void version(void);

int
main(int argc, char *argv[])
{
	char *secret = NULL;
	char *filename;
	char *username;
	char *password;
	char *realm;
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
		int	delete;
		int	create;
		int	runforever;
		int	from_stdin;
		int	verify;
	} flags =
	{
		0, 0, 0, 0, 0, 0, 1, 0, 1
	};

	const struct option options[] =
	{
		{"create",	no_argument,	NULL,		'c'},
		{"to-stdout",	no_argument,	NULL,		'n'},
		{"delete",	no_argument,	NULL,		'D'},
		{"from-stdin",	no_argument,	NULL,		'i'},
		{"help",	no_argument,	&flags.help,	1},
		{"version",	no_argument,	&flags.version,	1},
		{"no-verify",	no_argument,	&flags.verify, 0},
		{"mallocdebug", no_argument,	&flags.runforever, 1},
		{NULL,		0,		NULL,		0}
	};

	setprogname(argv[0]);

	while ((c = getopt_long(argc, argv, "cnDi", options, NULL)) != -1)
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
			case 'i':
				flags.from_stdin = 1;
				break;
			case 'D':
				flags.delete = 1;
				break;
			case 0:
				break;
			default:
				usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (flags.help)
		usage();

	if (flags.version)
		version();

	if (flags.delete)
	{
		if (argc < 2)
			syntax("you must specify a file and a username");
		delete_from_file(argv[0], argv[2], argv[1]);
		exit(EXIT_SUCCESS);
	}

	if (!flags.to_stdout)
	{
		if (argc < 3)
			syntax("you must specify a file, a realm and a username");
		filename = argv[0];
		realm = argv[1];
		username = argv[2];
	}
	else
	{
		if (argc < 2)
			syntax("you must specify a username and a realm");

		realm = argv[0];
		username = argv[1];
	}
	
	if (strlen(username) > MAX_STRING_LEN-1)
		errx(EXIT_OVERFLOW, "the username must not contain more than %i characters", MAX_STRING_LEN-1);

	if (strchr(username, ':') != NULL)
		errx(EXIT_ILLEGALCHARS, "the username must not contain the character ':'");

	if (strlen(realm) > MAX_STRING_LEN-1)
		errx(EXIT_OVERFLOW, "the realm must not contain more than %i characters", MAX_STRING_LEN-1);

	if (strchr(realm, ':') != NULL)
		errx(EXIT_ILLEGALCHARS, "the realm must not contain the character ':'");


	if (!flags.from_stdin)
	{
		password = readpasswd("Password:", buf, MAX_STRING_LEN, F_NOECHO);
		if (flags.verify)
		{
		       	password = readpasswd("Verify password:", buf1, MAX_STRING_LEN, F_NOECHO);
			if (strncmp(buf, buf1, MAX_STRING_LEN) != 0)
			{
				memset(buf, 0, MAX_STRING_LEN);
				errx(EXIT_VERIFICATION, "password mismatch");
			}
		}
	}

	if (flags.from_stdin)
		password = readpasswd("", buf, MAX_STRING_LEN, 0);

	if (strlen(password) > MAX_STRING_LEN-1)
		errx(EXIT_OVERFLOW, "the password must not contain more than %i characters", MAX_STRING_LEN-1);

	secret = digest_md5(username, realm, password, NULL);

	if (strlen(secret) + strlen(username) + 1 > MAX_STRING_LEN-1)
		errx(EXIT_OVERFLOW, "resultant user record must not exceed %i characters", MAX_STRING_LEN-1);

	if (!flags.to_stdout)
	{
		if (flags.create)
			create_file(filename, username, realm, secret);
		else
			update_file(filename, username, realm, secret);
	}
	else
		printf("%s:%s\n", username, secret);

	/* zero everything */
	memset(buf, 0, sizeof(buf));
	memset(password, 0, sizeof(password));
	memset(username, 0, sizeof(username));
	memset(realm, 0, sizeof(username));
	memset(secret, 0, sizeof(secret));

	return EXIT_SUCCESS;
}


void
usage(void)
{
	printf("Usage: %s [OPTIONS]... [FILE] REALM USERNAME\n", getprogname());
	printf("\n\
Options:\n\n\
  -c, --create                create FILE; overwrite FILE if it exists\n\
  -n, --to-stdout             write data to STDOUT instead of FILE\n\
  -D, --delete                delete USERNAME from FILE\n\
  -i, --from-stdin            read the password from STDIN instead of\n\
                              prompting for it\n\
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
	printf("%s - %s %s %s\n", getprogname(), PACKAGE_NAME, VERSION_LONG, OPENSSL_VERSION);
	printf("\
Copyright 2008, 2009, 2010, 2011, 2012 David Winter. All rights reserved.\n\
This is open source software, see the source for copying conditions.\n");
	exit(EXIT_SUCCESS);
}
