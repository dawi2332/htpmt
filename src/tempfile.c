/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
 */

/* $Id: tempfile.c 289 2008-12-24 00:32:17Z david $ */

#include "system.h"
#include "error.h"

#ifndef TMPFILE_TEMPLATE
#define TMPFILE_TEMPLATE "tmpXXXXXXXXXXXXXXXX"
#endif

/*
 * Creates a new temporary file using mkstemp(3) and returns the opened file.
 */
FILE *
tempfile()
{
	FILE *file;
	int fd;
	char temp[] = P_tmpdir/**/TMPFILE_TEMPLATE;
	mode_t mask = umask(S_IRWXG|S_IRWXO);

	fd = mkstemp(temp);


	if ((fd == -1) || (file = fdopen(fd, "r+")) == NULL)
	{
		close(fd);
		error(EXIT_FAILURE, "cannot create temporary file in %s", P_tmpdir);
	}

	remove(temp);
	memset(temp, 0, sizeof(temp));

	umask(mask);

	return file;
}
