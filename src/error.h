/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
 */

/* $Id: error.h 280 2008-12-17 19:57:09Z david $ */

#ifndef _ERROR_H
#define _ERROR_H
#ifndef __STRING
#define __STRING(x) "x"
#endif

#define DEBUG_STR(x) debug("%s (0x%x) = \"%s\"\n", __STRING(x), x, x)
#define DEBUG_INT(x) debug("%s (0x%x) = \"%i\"\n", __STRING(x), &x, x)
#define DEBUG_FLOAT(x) debug("%s (0x%x) = \"%f\"\n", __STRING(x), &x, x)

void debug(const char*, ...);
void error(int, const char*, ...);
void allocation_error();
#endif
