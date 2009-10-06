/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
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
