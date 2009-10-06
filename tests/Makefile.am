EXTRA_DIST = libmd.at libhtcore.at testsuite.at $(TESTSUITE) atlocal.in
DISTCLEANFILES = atconfig package.m4
CLEANFILES = testsuite.log
MAINTAINERCLEANFILES = testsuite Makefile.in

SUBDIRS = unittests

TESTSUITE = $(srcdir)/testsuite

check-local: atconfig atlocal $(TESTSUITE)
	$(SHELL) '$(TESTSUITE)' $(TESTSUITEFLAGS)

installcheck-local: atconfig atlocal $(TESTSUITE) 
	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(bindir)' $(TESTSUITEFLAGS) 

clean-local:
	test ! -f $(TESTSUITE) || $(SHELL) $(TESTSUITE) --clean

AUTOM4TE = $(SHELL) $(top_srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest 
$(TESTSUITE): $(srcdir)/testsuite.at $(srcdir)/package.m4 $(srcdir)/libmd.at
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $@.at 
	mv $@.tmp $@ 


.PHONY: libmd.at
libmd.at: $(top_builddir)/libmd/libmd.a
