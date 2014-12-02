/*
 * Copyright 2008-2014 David Winter
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

#include "system.h"

#if defined(HAVE_LIBCRYPTO)
#include <openssl/opensslv.h>

static char *openssl_version_string = NULL;

char *get_openssl_version() {
	if (openssl_version_string != NULL) {
		return openssl_version_string;
	}

	char buf[1024];
	unsigned int major = OPENSSL_VERSION_NUMBER >> 28 & 0xf;
	unsigned int minor = OPENSSL_VERSION_NUMBER >> 20 & 0xff;
	unsigned int micro = OPENSSL_VERSION_NUMBER >> 12 & 0xff;
	unsigned int patch = OPENSSL_VERSION_NUMBER >> 4 & 0xff;
	unsigned int status = OPENSSL_VERSION_NUMBER & 0xf;

	patch = (patch > 0 ? patch + 0x60 : 0);

	snprintf(buf, 1024, "openssl-%i.%i.%i%c", major, minor, micro, patch);
	if (status == 0)
	{
		strncat(buf, "-dev", 4);
	}
	if (status > 0 && status < 0xf)
	{
		char *tmp = buf + strlen(buf);
		snprintf(tmp, 6, "-beta%i", status);
	}

	openssl_version_string = strdup(buf);
	return openssl_version_string;
}
#endif
