MAINTAINERCLEANFILES = Makefile.in version.h
CLEANFILES = version.h.tmp
EXTRA_DIST = version.h

AM_CPPFLAGS = -I$(top_srcdir)/libmd/
LDADD = libhtcore.a $(top_builddir)/libmd/libmd.a

bin_PROGRAMS = htpasswd htdigest #htconvert
noinst_LIBRARIES = libhtcore.a

BUILT_SOURCES = version.h
libhtcore_a_SOURCES = system.h error.h error.c getpass.c getpass.h basic-auth.h basic-auth.c fileio.h fileio.c tempfile.h tempfile.c digest-auth.h digest-auth.c crypt-apr1.c crypt-apr1.h generate-salt.c generate-salt.h
libhtcore_a_DEPENDENCIES = $(top_builddir)/libmd/libmd.a

version.h.tmp: $(top_srcdir)/build-aux/version
	svn info >/dev/null 2>&1 \
	&& $< $(top_srcdir) > $@ \
	|| exit 0
version.h: version.h.tmp
	cmp $< $@ >/dev/null 2>&1 \
	|| cp $< $@ \
	|| exit 0

.PHONY: version.h.tmp
