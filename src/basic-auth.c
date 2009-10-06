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

/* $Id: basic-auth.c 286 2008-12-19 02:04:27Z david $ */

#include <system.h>
#include <sha.h>
#include <md5.h>
#include "generate-salt.h"
#include "crypt-apr1.h"

#ifdef HAVE_CRYPT_H
#include <crypt.h>
#endif

static unsigned const char itob64_s[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void
itob64(char *in, char *out, size_t length)
{
	char		*ptr = out;
	int		i;

	for (i = 0; i < length -2; i += 3)
	{
		*ptr++ = itob64_s[(in[i] >> 2) & 0x3f];
		*ptr++ = itob64_s[((in[i] & 0x3) << 4) |
			((in[i + 1] & 0xf0) >> 4)];
		*ptr++ = itob64_s[((in[i +1] & 0xf) << 2) |
			((in[i + 2] & 0xc0) >> 6)];
		*ptr++ = itob64_s[in[i + 2] & 0x3f];
	}

	if (i < length)
	{
		*ptr++ = itob64_s[(in[i] >> 2) & 0x3f];

		if (i == (length - 1))
		{
			*ptr++ = itob64_s[((in[i] & 0x3) << 4)];
			*ptr++ = '=';
		}
		else
		{
			*ptr++ = itob64_s[((in[i] & 0x3) << 4) |
				((in[i + 1] & 0xf0) >> 4)];
			*ptr++ = itob64_s[((in[i + 1] & 0xf) << 2)];
		}
		*ptr++ = '=';
	}
	*ptr++ = '\0';
}

char *
basic_crypt(char *user, char *realm, char *password, char* salt)
{
	static char secret[14];
	if (salt == NULL)
		salt = generate_salt(2);
	strncpy(secret, crypt(password, salt), 14);

	return secret;
}

char *
basic_sha1(char *user, char *realm, char *password, char *salt)
{
	SHA1_CTX	mdctx;
	unsigned char	md[SHA_DIGEST_LENGTH];
	char tmp[28];
	static char	secret[34];
	
	SHA1_Init(&mdctx);
	SHA1_Update(&mdctx, (unsigned char*) password, strlen(password));
	SHA1_Final(md, &mdctx);

	itob64((char *) md, tmp, SHA_DIGEST_LENGTH);
	
	memset(md, '\0', SHA_DIGEST_LENGTH);

	sprintf(secret, "{SHA}%s", tmp);

	memset(tmp, '\0', sizeof(tmp));

	return secret;
}

char *
basic_apr1(char *user, char *realm, char *password, char *salt)
{
	static char secret[120];
	if (salt == NULL)
		salt = generate_salt(8);
	strncpy(secret, crypt_apr1(password, salt), 120);
	return secret;
}
