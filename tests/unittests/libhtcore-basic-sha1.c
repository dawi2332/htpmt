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

	char result[10][34] = {
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
		assert(strcmp(basic_sha1(user, NULL, data[i], NULL), result[i]) == 0);
	}

	return 0;
}
