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
 * libhtcore-basic-sha1 -- unittest for basic_sha1().
 */

#include <system.h>
#include <basic-auth.h>
#include <assert.h>

const char *program_name = "libhtcore-basic-sha1";

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

	char expected[10][34] = {
		"{SHA}96OR7NAcqpk7WyK0z+JEXG2SSJE=",
		"{SHA}uswqhk+KRvrk5BV//Ue1s9SpaqM=",
		"{SHA}y+IZ4vF1d1Tn0FpMtDk+chIpbFA=",
		"{SHA}d01FA7FTLCSi8nJwZV1Ldmad9fw=",
		"{SHA}14spQ8/YwqPqWBcVZkEiE7o3gio=",
		"{SHA}H+7Cnz3Zo+yEfZd2iCR8Kly3g0g=",
		"{SHA}uo0Dqo2zSUPAhytFxdTs5vGb3Xo=",
		"{SHA}Tp1y6hGJEM9VxhPWZbxB7ZkG9g4=",
		"{SHA}GDHnO15oUsO4BnLZtUAVRVY1WaA=",
		"{SHA}heAiSmCp8fLL2Q/bRHbIEqRh31M=",
	};

	int i;
	char user[6] = "user";

	for (i = 0; i < 10; i++)
	{
		user[4] = 0x30 + i;
		assert(strcmp(basic_sha1(user, NULL, data[i], NULL), expected[i]) == 0);
	}

	return 0;
}
