MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST = fct.h

AM_CPPFLAGS = -I$(top_srcdir)/src -I$(top_srcdir)
LDADD = $(top_builddir)/src/libhtcore.a $(LIBMD) $(LIBCRYPTO)

check_PROGRAMS = htpmt_encryption htpmt_salt dummy_tests
TESTS = htpmt_encryption htpmt_salt
if ENABLE_LIBMD
check_PROGRAMS += libmd
TESTS += libmd
endif
##XFAIL_TESTS = 
