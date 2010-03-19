MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST = fct.h

AM_CPPFLAGS = -I$(top_srcdir)/src -I$(top_srcdir)/libmd
LDADD = $(top_builddir)/src/libhtcore.a $(top_builddir)/libmd/libmd.a

check_PROGRAMS = libmd htpmt_encryption htpmt_salt dummy_tests
TESTS = libmd htpmt_encryption htpmt_salt
##XFAIL_TESTS = 
