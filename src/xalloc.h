/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
 */

/* $Id: xalloc.h 277 2008-12-14 00:23:50Z david $ */

#ifndef _XALLOC_H
#define _XALLOC_H
void *xmalloc(size_t);
void *xrealloc(void *, size_t);
void *xcalloc(size_t, size_t);
void *xmemdup(const void *, size_t);
char *xstrdup(const char *);
#endif
