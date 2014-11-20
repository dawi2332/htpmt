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

#include <fcntl.h>
#include "fileio.h"
#include "tempfile.h"

void copy_file(FILE *in, FILE *out) {
	char buf[BUFSIZ];
	rewind(in);
	rewind(out);

	while (fgets(buf, BUFSIZ, in) != NULL) {
		fputs(buf, out);
	}
}

/*
 * create_file -- creates a new file with the given data
 */
void create_file(char *filename, char *username, char *realm, char *password) {
	FILE *out;
	struct stat sb;

	if ((out = fopen(filename, "w")) == NULL)
		err(EXIT_INVALIDFILE, "cannot not open \"%s\" for writing",
			filename);

	fprintf(out, "%s:%s\n", username, password);
	fprintf(stderr, "Added record for user %s\n", username);

	fclose(out);
}

/*
 * update_file -- updates or adds a password
 */
void update_file(char *filename, char *username, char *realm, char *password) {
	FILE *in, *out;
	struct stat sb;
	char buf[MAX_STRING_LEN * 3];
	char scratch[MAX_STRING_LEN * 3];
	char *field1, *field2, *field3;
	int found = 0;

	out = tempfile();

	if ((in = fopen(filename, "r")) == NULL)
		err(EXIT_INVALIDFILE, "cannot not open \"%s\" for reading",
			filename);

	while (fgets(buf, sizeof(buf), in) != NULL) {
		/* Don't touch comment lines or empty lines, ignore duplicate
                 * records
                 */
		if (buf[0] == '#' || buf[0] == '\n'|| found > 0) {
			fputs(buf, out);
			continue;
		}
		strncpy(scratch, buf, MAX_STRING_LEN);
		field1 = strtok(scratch, ":");
		field2 = strtok(NULL, ":");
		field3 = strtok(NULL, ":");

		if (strncmp(username, field1, MAX_STRING_LEN) == 0 && ((field3 == NULL && realm == NULL) || ((field3 != NULL && realm != NULL) && (strncmp(realm, field2, MAX_STRING_LEN) == 0)))) {
			if (password != NULL) {
				fprintf(out, "%s:%s\n", username, password);
				found++;
			} else {
				if (realm == NULL) {
					fprintf(stderr, "Deleted record for user %s\n", username);
                                } else {
                                        fprintf(stderr, "Deleted record for user %s in realm %s\n", username, realm);
                                }
			}
		} else {
			fputs(buf, out);
		}
	}

	if (found == 0 && password != NULL) {
		fprintf(out, "%s:%s\n", username, password);
		fprintf(stderr, "Added record for user %s\n", username);
	}

	if (found > 0) {
		fprintf(stderr, "Updated record for user %s\n", username);
        }

	fclose(in);
	in = fopen(filename, "w");

	copy_file(out, in);
	fclose(in);
	fclose(out);
}
