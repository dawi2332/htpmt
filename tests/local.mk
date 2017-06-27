check_PROGRAMS = htpmt_encryption htpmt_salt dummy_tests
htpmt_encryption_SOURCES = tests/htpmt_encryption.c \
			   tests/fct.h \
			   $(BASIC_AUTH_SRC) \
			   $(DIGEST_AUTH_SRC)
htpmt_salt_SOURCES = tests/htpmt_salt.c \
		     tests/fct.h \
		     src/generate-salt.c \
		     src/generate-salt.h
dummy_tests_SOURCES = tests/dummy_tests.c tests/fct.h

TESTS = htpmt_encryption htpmt_salt
XFAIL_TESTS = dummy_tests

if ENABLE_LIBMD
check_PROGRAMS += libmd_tests
libmd_tests_SOURCES = tests/libmd_tests.c tests/fct.h
TESTS += libmd_tests
endif

# vim:ft=automake
