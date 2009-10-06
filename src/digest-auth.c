/*
 * Copyright (c) 2008 David Winter (dawi2332@gmail.com)
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

/* $Id: digest-auth.c 287 2008-12-19 02:07:28Z david $ */

#include "system.h"
#include "md5.h"

char *
digest_md5(char *user, char *realm, char *password, char *salt)
{
	int		i;
	char		tmp[MD5_DIGEST_LENGTH * 3];
	MD5_CTX		ctx;
	unsigned char	md[MD5_DIGEST_LENGTH];
	unsigned int	md_len;
	unsigned char	*ptr;
	unsigned char 	buf[33];
	static char	secret[MAX_STRING_LEN * 3];

	snprintf(tmp, sizeof(tmp), "%s:%s:%s", user, realm, password);

	MD5Init(&ctx);
	MD5Update(&ctx, (unsigned char*) tmp, strlen(tmp));
	MD5Final(md, &ctx);

	ptr = buf;
	
	for (i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
		sprintf((char*) ptr, "%02x", md[i]);
		ptr += 2;
	}
	
	memset(tmp, '\0', sizeof(tmp));
	sprintf(secret, "%s:%s", realm, buf);
	memset(buf, '\0', sizeof(buf));

	return secret;
}

