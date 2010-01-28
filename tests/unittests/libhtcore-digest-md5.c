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

/*
 * libhtcore-digest-md5 -- unittest for digest_md5().
 */

#include <system.h>
#include <digest-auth.h>
#include <assert.h>

const char *program_name = "libhtcore-digest-md5";

int
main(int argc, char *argv[])
{
	char data[10][33] = {
		"ChgafooverZVtvru0CXgGsD6QN5j8piA",
		"gaiCysbqVE0wJqdWHFVvCvYoLcbEzPLV",
		"zIwRHLPSyA5s5La2vHEB5F6I5Gewz.So",
		"G/aD6poD7j/.Zccz77DODdErrjauMqdV",
		"7D6ymPbK5CLUStO0S4H24nYe3BAwg4sd",
		"B11HpWB5beUPopfC8AskD7NBqKZNkYun",
		"py976WnfNK0BlExXtc6WauWDf/m6aQcF",
		"wneWwtPz8lFlmMQB22ZA8WlyQXXhct9P",
		"myNuCeFZ59.WJIGQeOP5ok7DPMGL5Nah",
		"4F70eP1M4JjVQj.2JiOv52oBlNatlSaf",
	};

	char expected[10][33] = {
		"c0b04fb4dc63d34c4e26b7becca887c3",
		"7fa736cdbab018bcc6e11986b0555dca",
		"dd778cf3d54418667a1bdae14f7b7708",
		"e195aadc7fe33b86392a68f6b83b0ec2",
		"e426fdf169e440196da2430b779f6718",
		"f38e0f895ebdd2ca786e491ff1931336",
		"f46b8bc382171d359a6b1cddd9474e75",
		"89c8644251da13a42e2d234a03c9bded",
		"7b54ef855e4f4bcb6e600eb3f0a3a970",
		"c3c6732e37d56ef40f8160b6ebd96ac6",
	};

	int i;
	char user[6] = "user";
	char realm[7] = "realm";
	char result[60];

	for (i = 0; i < 10; i++)
	{
		user[4] = 0x30 + i;
		realm[5] = 0x30 + i;

		sprintf(result, "%s:%s", realm, expected[i]);
		assert(strcmp(digest_md5(user, realm, data[i], NULL), result) == 0);
	}

	return 0;
}
