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

#ifndef LIBHTPMT_SYSTEM_H
#define LIBHTPMT_SYSTEM_H

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

#if !HAVE_DECL_P_TMPDIR
/* /tmp should be present on all Unices I guess... */
#define P_tmpdir "/tmp/"
#endif

#define RANDOMDEV "/dev/random"

#ifndef errno
extern int errno;
#endif

#endif /* !LIBHTPMT_SYSTEM_H */
