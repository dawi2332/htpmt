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
