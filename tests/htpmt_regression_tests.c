#include <system.h>
#include "fct.h"
#include <generate-salt.h>

const char program_name[] = "htpmt_regression_tests";

FCT_BGN()
{
	FCT_QTEST_BGN(htpmt__salt_uniqueness)
	{
		#define NUMSALTS 1024
		char salts[NUMSALTS][33];
		unsigned int duplicate_salts = 0;
		int i, j;

		for (i = 0; i < NUMSALTS; i++)
		{
			strcpy((char *) salts[i], generate_salt(32));
		}

		for (i = 0; i < NUMSALTS; i++)
		{
			for (j = i+1; j < NUMSALTS; j++)
			{
				fct_chk_neq_str(salts[i], salts[j]);
			}
		}
	}
	FCT_QTEST_END();
}
FCT_END();
