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

/* $Id: htconvert.c 286 2008-12-19 02:04:27Z david $ */

char *program_name;

#include "system.h"
#include "error.h"
#include "digest-auth.h"
#include "basic-auth.h"

typedef char* (*encrypt_t) (char*, char*, char*, char*);

void usage(void);
void version(void);
char *wrap_encrypt(encrypt_t, char*, char*, char*);
int simple_filter(char*, char*, char*);

int
main(int argc, char *argv[])
{
	program_name = argv[0];

	FILE *outfile = stdout;
	FILE *infile = stdin;
	char *realm;
	char *filtercmd;
	char *username;
	char *secret;
	char buf[BUFSIZ];
	char buf1[BUFSIZ];
	char *ptr;
	encrypt_t encrypt;
	int filter_count = 0;
	char c;

	static struct
	{
		int	version;
		int	help;
		int	from_file;
		int	to_file;
		int	ext_filter;
		int	basic_sha1;
		int	basic_md5;
		int	basic_crypt;
		int	digest_md5;
	} flags =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	const struct option options[] =
	{
		{"help",	no_argument,	&flags.help,	1},
		{"version",	no_argument,	&flags.version,	1},
		{"in",		required_argument, NULL,	'i'},
		{"out",		required_argument, NULL,	'o'},
		{"realm",	required_argument, NULL,	'r'},
		{"filter",	required_argument, NULL,	'f'},
		{"basic-sha1",	no_argument,	&flags.basic_sha1, 's'},
		{"basic-md5",	no_argument,	&flags.basic_md5, 'm'},
		{"basic-crypt",	no_argument,	&flags.basic_crypt, 'c'},
		{"digest-md5",	no_argument,	&flags.digest_md5, 'd'},
		{NULL,		0,		NULL,		0}
	};

	while ((c = getopt_long(argc, argv, "hvi:o:r:f:smcd", options, NULL)) != -1)
	{
		switch (c)
		{
			case 'i':
				if ((infile = fopen(optarg, "r")) == NULL)
					error(EXIT_INVALIDFILE, "cannot not open \"%s\" for reading", optarg);
				flags.from_file = 1;
				break;
			case 'o':
				if ((outfile = fopen(optarg, "w")) == NULL)
					error(EXIT_INVALIDFILE, "cannot not open \"%s\" for reading", optarg);
				flags.to_file = 1;
				break;
			case 'r':
				realm = optarg;
				break;
			case 'f':
				filtercmd = optarg;
				flags.ext_filter = 1;
				break;
			case 's':
				flags.basic_sha1 = 1;
				break;
			case 'm':
				flags.basic_md5 = 1;
				break;
			case 'c':
				flags.basic_crypt = 1;
				break;
			case 'd':
				flags.digest_md5 = 1;
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

	if ((flags.basic_md5 + flags.basic_crypt + flags.basic_sha1 + flags.digest_md5) > 1)
		syntax("please only one of `--basic-sha1', `--basic-md5', `--basic-crypt' or `--digest-md5'");
	if ((flags.basic_md5 + flags.basic_crypt + flags.basic_sha1 + flags.digest_md5) < 1)
		syntax("please one of `--basic-sha1', `--basic-md5', `--basic-crypt' or `--digest-md5'");

	if (flags.digest_md5 && realm == NULL)
		syntax("the `--digest-md5' option requires setting the realm (`--realm')");
	

	DEBUG_STR(filtercmd);	
	DEBUG_INT(flags.basic_sha1);
	DEBUG_INT(flags.basic_md5);
	DEBUG_INT(flags.basic_crypt);
	DEBUG_INT(flags.digest_md5);



	if (flags.basic_sha1)
		encrypt = basic_sha1_r;
	if (flags.basic_crypt)
		encrypt = basic_crypt_r;
	if (flags.basic_md5)
		encrypt = basic_apr1_r;
	if (flags.digest_md5)
		encrypt = digest_md5;

	while (fgets(buf, sizeof(buf), infile) != NULL)
	{
		if (buf[0] == '#' || buf[0] == '\n')
		{
			fputs(buf, outfile);
			continue;
		}

		ptr = strrchr(buf, '\n');
		if (ptr != NULL)
			*ptr = '\0';
		strncpy(buf1, buf, sizeof(buf));
		ptr = strchr(buf1, ':');
		if (ptr != NULL)
		{
			username = buf1;
			*ptr = '\0';
		}
		secret = ++ptr;

		if (!flags.ext_filter || (flags.ext_filter && simple_filter(filtercmd, username, secret)))
		{
			secret = wrap_encrypt(encrypt, username, realm, secret);
			fprintf(outfile, "%s:%s\n", username, secret);
			/* wipe secret */
			memset(secret, 0, sizeof(secret));
		}
		else
			fputs(buf, outfile);
	}



	/* do a little cleanup */
	if (flags.from_file)
		fclose(infile);
	if (flags.to_file)
		fclose(outfile);
	
	
	return EXIT_SUCCESS;
}


void
usage(void)
{
	printf("Usage: %s [OPTIONS]...\n", program_name);
	exit(EXIT_SUCCESS);
}

void
version(void)
{
	printf("%s - %s %s\n", program_name, PACKAGE_NAME, PACKAGE_VERSION);
	printf("\
Copyright (c) 2008 David Winter (dawi2332@gmail.com). All rights reserved.\n\
This is open source software, the the source for copying conditions.\n");
	exit(EXIT_SUCCESS);
}

char *
wrap_encrypt(encrypt_t function, char *username, char *realm, char *password)
{
	return function(username, realm, password, NULL);
}

int
simple_filter(char *filtercmd, char *username, char *secret)
{
	if (filtercmd == NULL)
		return 1;

	/*
	 * TODO: exec filtercmd
	 */

	return 1;
}
