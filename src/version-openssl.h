/*
 * Copyright 2011 David Winter
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>

#if defined(HAVE_LIBCRYPTO)
#include <openssl/opensslv.h>
#define openssl_major (OPENSSL_VERSION_NUMBER >> 28 & 0xff) + 0x30
#define openssl_minor (OPENSSL_VERSION_NUMBER >> 20 & 0xff) + 0x30
#define openssl_micro (OPENSSL_VERSION_NUMBER >> 12 & 0xff) + 0x30
#define openssl_patch (OPENSSL_VERSION_NUMBER >> 4 & 0xff) + 0x60
#define OPENSSL_VERSION _openssl_version()
static char *_openssl_version(void)
{
	static char version[20];
	sprintf(version, "openssl-%c.%c.%c%c", openssl_major, openssl_minor, openssl_micro, openssl_patch);
	return version;
}
#else
#define OPENSSL_VERSION ""
#endif
