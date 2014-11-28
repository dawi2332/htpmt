MAINTAINERCLEANFILES = Makefile.in version.h version-openssl.h
CLEANFILES = version.h.tmp version-openssl.h.tmp
EXTRA_DIST = version.h version-openssl.h

LDADD = libhtcore.a $(LIBMD) $(LIBCRYPTO)
AM_CPPFLAGS = -I$(top_srcdir)

bin_PROGRAMS = htpasswd htdigest
noinst_LIBRARIES = libhtcore.a

BUILT_SOURCES = version.h version-openssl.h
libhtcore_a_SOURCES = system.h syntax.c syntax.h progname.h progname.c basic-auth.h basic-auth.c fileio.h fileio.c tempfile.h tempfile.c digest-auth.h digest-auth.c crypt-apr1.c crypt-apr1.h generate-salt.c generate-salt.h readpasswd.c readpasswd.h sha.h md5.h

VCS_CHECK=git describe --always

version.h: $(top_srcdir)/build-aux/version
	$(VCS_CHECK) >/dev/null 2>&1 \
	&& $< $(abs_top_srcdir) > $@ \
	|| exit 0
version-openssl.h: $(top_srcdir)/build-aux/openssl-version
	$(VCS_CHECK) >/dev/null 2>&1 \
	&& $< $(abs_top_srcdir) > $@ \
	|| exit 0
