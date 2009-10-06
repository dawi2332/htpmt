/*
 * libhtcore-basic-apr1 -- unittest for basic_apr1().
 */

#include <system.h>
#include <basic-auth.h>
#include <assert.h>

#define SALT "salt1234"

const char *program_name = "libhtcore-basic-apr1";

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

	char result[10][23] = {
		"N/DXuXVvII8lpdPVtEwn1/",
		".NuvJ8S6uuIa4QOefbArj/",
		"zkZ296/nFqwPPvz28rLjv0",
		"goxq30WTsyNbxxqqye/45/",
		"PBB2vPKS.EQwAm3koG6oQ/",
		"6ObwKjQ8h/d8siIsuG2KQ1",
		"0YKRHHqFIl6MTxuJPV7Jl0",
		"IM2M5S.vAtLV2.jUN5IrP0",
		"OOLpek1B1ccaq3b3gnqKs.",
		"kLQL8hGBqTgUfUDP.1wJF1",
	};

	int i;
	char user[6] = "user";
	char result_string[60];

	for (i = 0; i < 10; i++)
	{
		user[4] = 0x30 + i;
		sprintf((char *) result_string, "$apr1$%s$%s",SALT, result[i]);
		assert(strcmp(basic_apr1(user, NULL, data[i], SALT), result_string) == 0);
	}


	return 0;
}
