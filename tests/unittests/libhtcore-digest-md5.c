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

	char result[10][33] = {
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
	char result_string[60];

	for (i = 0; i < 10; i++)
	{
		user[4] = 0x30 + i;
		realm[5] = 0x30 + i;

		sprintf(result_string, "%s:%s", realm, result[i]);
		assert(strcmp(digest_md5(user, realm, data[i], NULL), result_string) == 0);
	}

	return 0;
}
