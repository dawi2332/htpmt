#include <system.h>
#include "fct.h"
#include <basic-auth.h>
#include <digest-auth.h>

#define SALT "salt1234"

FCT_BGN()
{
	FCT_FIXTURE_SUITE_BGN(htpmt_encryption)
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

		char expected_apr1[10][23] = {
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
		char expected_crypt[10][14] = {
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
		char expected_sha1[10][34] = {
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
		char expected_digestmd5[10][33] = {
			"dce83ca55bbe4c10233de00883260c3a",
			"9dfca6f2de76fc56ea4d71cbd8a7f298",
			"b7ebcbde113c85e64f6fb548dbe9fb8b",
			"8cc1c02ee4b02593172073827df52ccc",
			"a78a5de911de83cf700e24fd66f975f8",
			"ca1969d106ad0e9a017d4fe6f07b71e2",
			"5b6a825cb6b58a77af892fb87e09de4b",
			"71645538fd44a436b92739f8ba11275f",
			"8b3a3955bc1bd920afa692189e73018e",
			"fd60e7a02c2a33d896bad41e151e1e75",
		};

		FCT_SETUP_BGN()
		{
		} FCT_SETUP_END();

		FCT_TEARDOWN_BGN()
		{
		} FCT_TEARDOWN_END();

		FCT_TEST_BGN(htpmt__apr1_encryption)
		{
			int i;
			char expected[60];
			char user[6] = "user";

			for (i = 0; i < 10; i++)
			{
				sprintf((char *) expected, "$apr1$%s$%s",SALT,
					expected_apr1[i]);
				fct_chk_eq_str(basic_apr1(user, NULL, data[i],
						SALT), expected);
			}
				
		} FCT_TEST_END();

		FCT_TEST_BGN(htpmt__crypt_encryption)
		{
			int i;
			char user[6] = "user";

			for (i = 0; i < 10; i++)
			{
				user[4] = 0x30 + i;
				fct_chk_eq_str(basic_crypt(user, NULL, data[i],
						SALT), expected_crypt[i]);
			}
				
		} FCT_TEST_END();

		FCT_TEST_BGN(htpmt__sha1_encryption)
		{
			int i;
			char user[6] = "user";

			for (i = 0; i < 10; i++)
			{
				user[4] = 0x30 + i;
				fct_chk_eq_str(basic_sha1(user, NULL, data[i],
						NULL), expected_sha1[i]);
			}
				
		} FCT_TEST_END();

		FCT_TEST_BGN(htpmt__md5_encryption)
		{
			int i;
			char user[6] = "user";
			char realm[7] = "realm";
			char expected[60];

			for (i = 0; i < 10; i++)
			{
				user[4] = 0x30 + i;
				realm[5] = 0x30 + i;

				sprintf(expected, "%s:%s", realm,
					expected_digestmd5[i]);
				fct_chk_eq_str(digest_md5(user, realm, data[i],
						NULL), expected);
	}
		} FCT_TEST_END();

	} FCT_FIXTURE_SUITE_END();
} FCT_END();

