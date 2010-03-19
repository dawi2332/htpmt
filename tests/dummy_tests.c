#include "fct.h"

FCT_BGN()
{
	void *data = NULL;
	FCT_FIXTURE_SUITE_BGN(dummy_suite)
	{
		FCT_SETUP_BGN()
		{
			data = malloc(sizeof(10));
		}
		FCT_SETUP_END();

		FCT_TEARDOWN_BGN()
		{
			free(data);
			data = NULL;
		}
		FCT_TEARDOWN_END();

		FCT_TEST_BGN(dummy__pass_test)
		{
			fct_req(data != NULL);
			fct_chk(sizeof(data) && "Dummy test failed!");
		}
		FCT_TEST_END();
	}
	FCT_FIXTURE_SUITE_END();

	FCT_QTEST_BGN(dummy__xfail_test)
	{
		fct_chk(!"This test is expected to fail (XFAIL).");
	}
	FCT_QTEST_END();
}
FCT_END();
