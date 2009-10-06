/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
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

