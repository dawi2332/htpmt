DISTCLEANFILES = atconfig package.m4
MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/src -I$(top_srcdir)/libmd
LDADD = $(top_builddir)/src/libhtcore.a $(top_builddir)/libmd/libmd.a

noinst_PROGRAMS = htpmt_unittests libmd_unittests htpmt_regression_tests

htpmt_unittests_SOURCES = htpmt_unittests.c fct.h
libmd_unittests_SOURCES = libmd_unittests.c fct.h
htpmt_regression_tests_SOURCES = htpmt_regression_tests.c fct.h

TESTS = libmd_unittests htpmt_unittests htpmt_regression_tests
