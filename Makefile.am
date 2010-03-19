SUBDIRS = contrib libmd src doc man tests
MAINTAINERCLEANFILES = aclocal.m4 configure config.h.in Makefile.in $(distdir).tar.gz $(distdir).tar.bz2

# Create ChangeLog on the fly during 'make dist'
dist-hook:
	$(srcdir)/build-aux/missing --run svn info $(abs_srcdir) \
	    	>/dev/null 2>&1 \
	       	&& $(srcdir)/build-aux/missing --run svn log -g $(abs_srcdir) \
	       	| $(srcdir)/contrib/gnuify-changelog  > $(distdir)/ChangeLog \
		|| exit 0
