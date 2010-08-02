SUBDIRS = build-aux contrib lib src doc man tests
MAINTAINERCLEANFILES = aclocal.m4 configure config.h.in Makefile.in $(distdir).tar.gz $(distdir).tar.bz2

dist-hook:
	@if svn info $(abs_srcdir) >/dev/null 2>&1; then \
		svnversion=`svnversion $(abs_srcdir)`; \
		if echo $${svnversion} | grep --silent ":"; then \
			echo "Error: cannot make dist from a mixed-revision working copy: $${svnversion}"; \
			exit 1; \
		fi; \
		if echo $${svnversion}  | grep --silent "M"; then \
			echo "Error: cannot make dist from a modified working copy: $${svnversion}"; \
			exit 1; \
		fi; \
		if echo $${svnversion}  | grep --silent "S"; then \
			echo "Error: cannot make dist from a switched working copy: $${svnversion}"; \
			exit 1; \
		fi; \
		/usr/bin/env echo -n "Populating ChangeLog... "; \
	       	svn log -g $(abs_srcdir) \
	       	| $(srcdir)/contrib/gnuify-changelog  > $(distdir)/ChangeLog ; \
		echo Done; \
	fi
