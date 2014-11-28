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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>

#if defined(HAVE_LIBCRYPTO)
#include <openssl/opensslv.h>
#endif

void
print_openssl_version(unsigned long version_number)
{
	unsigned int major = version_number >> 28 & 0xf;
	unsigned int minor = version_number >> 20 & 0xff;
	unsigned int micro = version_number >> 12 & 0xff;
	unsigned int patch = version_number >> 4 & 0xff;
	unsigned int status = version_number & 0xf;

	patch = (patch > 0 ? patch + 0x60 : 0);

	printf("openssl-%i.%i.%i%c", major, minor, micro, patch);
	if (status == 0)
	{
		printf("-dev");
	}
	if (status > 0 && status < 0xf)
	{
		printf("-beta%i", status);
	}
}

int
main(int arc, char *argv[])
{
	printf("#define OPENSSL_VERSION \"");
#ifdef OPENSSL_VERSION_NUMBER
	print_openssl_version(OPENSSL_VERSION_NUMBER);
#endif
	puts("\"");
}
