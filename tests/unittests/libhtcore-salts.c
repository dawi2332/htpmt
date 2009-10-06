/*
 * libhtcore-salts -- simple unittest for generate_salt()
 */

#include <system.h>
#include <generate-salt.h>
#include <assert.h>

#define NUMSALTS 1024

const char *program_name = "libhtcore-salts";

int
main(int argc, char *argv[])
{
	char salts[NUMSALTS][33];
	unsigned int duplicate_salts = 0;
	int i, j;

	for (i = 0; i < NUMSALTS; i++)
	{
		strcpy((char *) salts[i], generate_salt(32));
	}

	for (i = 0; i < NUMSALTS; i++)
	{
		for (j = 0; j < NUMSALTS; j++)
		{
			if (strcmp((char *) salts[i], (char *) salts[j]) == 0 && i != j)
			{
				duplicate_salts++;
			}
		}
	}

	assert(duplicate_salts < 1);

	return 0;
}
