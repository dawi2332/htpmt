/*
 * Copyright 2008, 2009, 2010 David Winter
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
		err(EXIT_FAILURE, "cannot create temporary file in %s", P_tmpdir);
	}

	remove(temp);
	memset(temp, 0, sizeof(temp));

	umask(mask);

	return file;
}
