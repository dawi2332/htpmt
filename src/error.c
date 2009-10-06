/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com). All rights reserved.
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
 */

/* $Id: error.c 280 2008-12-17 19:57:09Z david $ */

#include <system.h>
#ifndef program_name
extern char *program_name;
#endif

void
debug(const char *format, ...)
{
	va_list args;
	fprintf(stderr, "DEBUG >>> ");
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
}

void
error(int status, const char *format, ...)
{
	va_list args;

	fflush(stdout);

	fprintf(stderr, "%s: ", program_name);
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	if (errno)
	{
		fprintf(stderr, ": %s", strerror(errno));
	}
	fprintf(stderr, "\n");

	fflush(stderr);

	exit(status);
}

void syntax(const char *format, ...)
{
	va_list args;

	fflush(stdout);

	fprintf(stderr, "%s: ", program_name);
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	fprintf(stderr, "\nTry `%s --help' for more information.\n", program_name);

	fflush(stderr);

	exit(EXIT_SYNTAXERROR);
}


void
warn(const char *format, ...)
{
	va_list args;

	fflush(stdout);

	fprintf(stderr, "WARNING: ");
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);

	fflush(stderr);
}

void
allocation_error(void)
{
	error(EXIT_ALLOCATION, "memory allocation error");
}

