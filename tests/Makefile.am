MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST = fct.h

AM_CPPFLAGS = -I$(top_srcdir)/src -I$(top_srcdir)/libmd
LDADD = $(top_builddir)/src/libhtcore.a $(top_builddir)/libmd/libmd.a

check_PROGRAMS = libmd_unittests htpmt_unittests htpmt_regression_tests dummy_tests
TESTS = libmd_unittests htpmt_unittests htpmt_regression_tests #dummy_tests
XFAIL_TESTS = dummy_tests
