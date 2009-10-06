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
 * libhtcore-basic-crypt -- basic_crypt() unittest.
 */

#include <system.h>
#include <basic-auth.h>
#include <assert.h>

#define SALT "sa"

const char *program_name = "libhtcore-basic-crypt";

int
main(int argc, char *argv[])
{
	char data[10][33] = {
		"eBpaj2MFS5dwCJoOR4f69H6KOpo1jVGD",
		"6GHHuzWA/qmZnMtXHNCH8AQsRf0kdIKZ",
		"q65TykyNjSMntZaq9T0fNLg.8WZbxyye",
		"YapuaKtO6gbbkLHCE8HquWF4Da99Imtj",
		"w4gjsv1xCM6qIv..MWZyLL13mhcK1eCn",
		"ccnUjs3GaxhvdYNfbCQ.Yaecfb2mzx3R",
		"OU.6ikq.hMTPyprSKvCwTHqpOt.6i0Ey",
		"ngnIWcPpKRW2GN.5bsjg21NN5gwvQCf6",
		"turqIGuaIVpcamYaXbm.N3DWYarQ.Htt",
		"0RV1DZ/Gq4tyhQkPLedaeL6YHQDWwJ/n",
	};

	char result[10][14] = {
		"saakIhz/U1RX6",
		"sa2C0o5tu0AY2",
		"saSuUcxYOKG86",
		"sapGerimE5uCc",
		"savaT90Qlq45g",
		"sarYTkHeTcRxM",
		"sa0Fj5nmjRg5Y",
		"sadi1V9G8EAsQ",
		"sacdWpgate8CM",
		"sa0wsrQjuF/2Q",
	};

	int i;
	char user[6] = "user";

	for (i = 0; i < 10; i++)
	{
		user[4] = 0x30 + i;
		assert(strcmp(basic_crypt(user, NULL, data[i], SALT), result[i]) == 0);
	}

	return 0;
}
