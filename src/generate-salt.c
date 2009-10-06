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

/* $Id: generate-salt.c 286 2008-12-19 02:04:27Z david $ */

#include <system.h>
#include <fcntl.h>

#ifdef HAVE_RANDOM
#define RAND random
#else
#ifdef HAVE_RAND
#define RAND rand
#endif /* HAVE_RAND */
#endif /* HAVE_RANDOM */

int rand_seeded = 0;
static unsigned const char itoa64_s[] =
	"./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

/*
 * seed_random -- seed random(3) or rand(3) with entropy from RANDOMDEV
 */
void
seed_random(void)
{
#ifdef HAVE_RANDOM
	unsigned long seed;
#else
#ifdef HAVE_RAND
	unsigned int seed;
#endif /* HAVE_RAND */
#endif /* HAVE_RANDOM */

	const size_t len = sizeof(seed);
	int fd = open(RANDOMDEV, O_RDONLY, 0);
	if (fd > 0)
	{
		if (read(fd, (void *) &seed, len) != (size_t) len)
		{
			close(fd);	
			error(EXIT_FAILURE, "reading from '%s' doesn't yield enough entropy to seed the pseudo-random number generator", RANDOMDEV);
		}
	}
	else
	{
		error(EXIT_FAILURE, "failed to seed the pseudo-random number generator with '%s'", RANDOMDEV);
	}

	close(fd);

#ifdef HAVE_RANDOM
	srandom(seed);
#else
#ifdef HAVE_RAND
	srand((unsigned int) seed);
#endif /* HAVE_RAND */
#endif /* HAVE_RANDOM */

	return;
}


/* 
 * generate_salt -- generates a random string, up to 32 characters long.
 */
char *
generate_salt(size_t length)
{
	static char salt[33];
	int i;

	if (!rand_seeded)
	{
		seed_random();
		rand_seeded = 1;
	}

	for (i = 0; i < 32; i++)
	{
		salt[i] = itoa64_s[RAND() & 0x3f];
	}
	

	if (0 < length < 32)
		salt[length+1] = '\0';
	else
		salt[32] = '\0';

	
	return salt;
}
