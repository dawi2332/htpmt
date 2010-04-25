MAINTAINERCLEANFILES = Makefile.in version.h
CLEANFILES = version.h.tmp
EXTRA_DIST = version.h

LDADD = libhtcore.a $(LIBMD) $(LIBCRYPTO)
AM_CPPFLAGS = -I$(top_srcdir)

bin_PROGRAMS = htpasswd htdigest
noinst_LIBRARIES = libhtcore.a

BUILT_SOURCES = version.h
libhtcore_a_SOURCES = system.h error.c basic-auth.h basic-auth.c fileio.h fileio.c tempfile.h tempfile.c digest-auth.h digest-auth.c crypt-apr1.c crypt-apr1.h generate-salt.c generate-salt.h readpasswd.c readpasswd.h sha.h md5.h

version.h.tmp: $(top_srcdir)/build-aux/version
	svn info >/dev/null 2>&1 \
	&& $< $(abs_top_srcdir) > $@ \
	|| exit 0
version.h: version.h.tmp
	cmp $< $@ >/dev/null 2>&1 \
	|| cp $< $@ \
	|| exit 0

.PHONY: version.h.tmp
