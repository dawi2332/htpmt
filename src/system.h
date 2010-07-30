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

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <config.h>
#include <stdio.h> 
#if HAVE_SYS_TYPES_H 
#	include <sys/types.h> 
#endif  /* HAVE_SYS_TYPES_H */
#if HAVE_SYS_STAT_H 
#	include <sys/stat.h> 
#endif  /* HAVE_SYS_STAT_H */
#if STDC_HEADERS 
#	include <stdlib.h> 
#	include <stddef.h> 
#	include <stdarg.h>
#else 
#	ifdef HAVE_STDLIB_H 
#	include <stdlib.h> 
#	endif  /* HAVE_STDLIB_H */
#endif  /* STDC_HEADERS */
#if HAVE_STRING_H 
#	if !defined STDC_HEADERS && defined HAVE_MEMORY_H 
#		include <memory.h> 
#	endif  /* !STDC_HEADERS && HAVE_MEMORY_H */
#	include <string.h> 
#endif  /* HAVE_STRING_H */
#if HAVE_STRINGS_H 
#	include <strings.h> 
#endif  /* HAVE_STRINGS_H */
#if HAVE_INTTYPES_H 
#	include <inttypes.h> 
#endif /* HAVE_INTTYPES_H */
#ifdef HAVE_STDINT_H 
#	include <stdint.h> 
#endif  /* HAVE_STDINT_H */
#if HAVE_UNISTD_H 
#	include <unistd.h> 
#endif /* HAVE_UNISTD_H */
#ifdef HAVE_GETOPT_H
#	include <getopt.h>
#endif /* HAVE_GETOPT_H */
#ifdef HAVE_SYS_PARAMS_H
#	include <sys/params.h>
#endif /* HAVE_SYS_PARAMS_H */
#ifdef HAVE_ERRNO_H
#	include <errno.h>
#endif
#ifdef HAVE_ERR_H
#	include <err.h>
#endif

#define MAX_STRING_LEN 256

#ifndef HAVE_DECL_P_TMPDIR
/* /tmp should be present on all Unices I guess... */
#define P_tmpdir "/tmp/"
#endif

#ifdef HAVE_GETPROGNAME
#define PROGNAME() getprogname()
#else
#ifdef HAVE_DECL___PROGNAME__
#define PROGNAME() basename(__progname())
#elif HAVE_DECL___PROGNAME
#define PROGNAME() basename(__progname())
#else
#warning "Can't figure a way to determine program name at runtime, defaulting to \"htpmt\"."
#define PROGNAME() return "htpmt"
#endif /* HAVE_DECL___PROGNAME__ */
#endif /* !HAVE_GETPROGNAME */

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#define EXIT_FILEPERM 1
#define EXIT_SYNTAXERROR 2
#define EXIT_VERIFICATION 3
#define EXIT_INTERRUPT 4
#define EXIT_OVERFLOW 5
#define EXIT_ILLEGALCHARS 6
#define EXIT_INVALIDFILE 7
#define EXIT_ALLOCATION 8

#define RANDOMDEV "/dev/random"

#ifndef errno
extern int errno;
#endif

#ifndef exit
extern void exit();
#endif

#endif /* !_SYSTEM_H */
