/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
 */

/* $Id: fileio.c 289 2008-12-24 00:32:17Z david $ */

#include <fcntl.h>
#include "fileio.h"
#include "tempfile.h"

void *
copy_file(FILE *in, FILE *out)
{
	char buf[BUFSIZ];
	rewind(in);
	rewind(out);

	while (fgets(buf, BUFSIZ, in) != NULL)
	{
		fputs(buf, out);
	}
}

/* 
 * create_file -- creates a new file with the given data
 */
void
create_file(char *filename, char *username, char *realm, char *password)
{
	FILE *out;
	struct stat sb;

	if ((out = fopen(filename, "w")) == NULL)
		error(EXIT_INVALIDFILE, "cannot not open \"%s\" for writing", filename);

	fprintf(out, "%s:%s\n", username, password);
	fprintf(stderr, "Added record for user %s\n", username);

	fclose(out);
}

/*
 * update_file -- updates or adds a password
 */
void
update_file(char *filename, char *username, char *realm, char *password)
{
	FILE *in, *out;
	struct stat sb;
	char buf[MAX_STRING_LEN * 3];
	char scratch[MAX_STRING_LEN * 3];
	char *column1, *column2, *column3;
	int found = 0;

	out = tempfile();

	if ((in = fopen(filename, "r")) == NULL)
		error(EXIT_INVALIDFILE, "cannot not open \"%s\" for reading", filename);

	while (fgets(buf, sizeof(buf), in) != NULL)
	{
		if (buf[0] == '#' || buf[0] == '\n')
		{
			fputs(buf, out);
			continue;
		}
		strncpy(scratch, buf, MAX_STRING_LEN);
		column1 = strtok(scratch, ":");
		column2 = strtok(NULL, ":");
		column3 = strtok(NULL, ":");

		if (strncmp(username, column1, MAX_STRING_LEN) == 0 &&
			(realm != NULL &&
			 strncmp(realm, column2, MAX_STRING_LEN) == 0))
		{
			if (password != NULL)
			{
				fprintf(out, "%s:%s\n", username, password);
				found++;
			}
			else
				fprintf(stderr, "Deleted record for user %s\n", username);
		}
		else
		{
			fputs(buf, out);
		}
	}

	if (found == 0 && password != NULL)
	{
		fprintf(out, "%s:%s\n", username, password);
		fprintf(stderr, "Added record for user %s\n", username);
	}

	if (found > 0)
		fprintf(stderr, "Updated record for user %s\n", username);

	fclose(in);
	in = fopen(filename, "w");

	copy_file(out, in);
	fclose(in);
	fclose(out);
}
