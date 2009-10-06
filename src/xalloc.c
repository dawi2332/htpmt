/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
 */

/* $Id: xalloc.c 277 2008-12-14 00:23:50Z david $ */

#include "error.h"
#include <stdlib.h>
#include <string.h>

#define CHECKPTR(a,b) if (a == NULL && b != 0) allocation_error();

void *
_checkptr(void *ptr, size_t size)
{
	if(ptr == NULL && size != 0)
	{
		allocation_error();
	}
}


void *
xmalloc(size_t size)
{
	void *ptr = malloc(size);
	CHECKPTR(ptr, size);
	return ptr;
}

void *
xrealloc(void *ptr, size_t size)
{
	ptr = realloc(ptr, size);
	_checkptr(ptr, size);
	return ptr;
}

void *
xcalloc(size_t count, size_t size)
{
	void *ptr = calloc(count, size);
	_checkptr(ptr, size);
	return ptr;
}

void *
xmemdup(const void *ptr, size_t size)
{
	void *new_ptr = xmalloc(size);
	memcpy(new_ptr, ptr, size);
	return new_ptr;
}

char *
xstrdup(const char *str)
{
	return xmemdup(str, strlen(str) + 1);
}
