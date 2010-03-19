#include <system.h>
#include "fct.h"
#include <generate-salt.h>

FCT_BGN()
{
	#define NUMSALTS 1024
	char salts[NUMSALTS][33];
	unsigned int duplicate_salts = 0;
	int i, j;

	FCT_FIXTURE_SUITE_BGN(htpmt__salt)
	{
		FCT_SETUP_BGN()
		{
			for (i = 0; i < NUMSALTS; i++)
			{
				strcpy((char *) salts[i], generate_salt(32));
			}
		}
		FCT_SETUP_END();

		FCT_TEARDOWN_BGN()
		{
			memset(salts, '\0', sizeof(salts));
		}
		FCT_TEARDOWN_END();
		
		FCT_TEST_BGN(htpmt__salt_entropy)
		{
			fct_req(salts != NULL);

			for (i = 0; i < NUMSALTS; i++)
			{
				for (j = i+1; j < NUMSALTS; j++)
				{
					fct_chk_neq_str(salts[i], salts[j]);
				}
			}
		}
		FCT_TEST_END();
	}
	FCT_FIXTURE_SUITE_END();
		
}
FCT_END();
