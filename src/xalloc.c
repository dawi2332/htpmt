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
