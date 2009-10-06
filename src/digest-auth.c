/*
 * Copyright (C) 2008 David Winter (dawi2332@gmail.com).
 * All rights reserved.
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

