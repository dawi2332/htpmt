MAINTAINERCLEANFILES = Makefile.in

LDADD = libhtcore.a $(LIBMD) $(LIBCRYPTO)
AM_CPPFLAGS = -I$(top_srcdir)

bin_PROGRAMS = htpasswd htdigest
noinst_LIBRARIES = libhtcore.a

libhtcore_a_SOURCES = system.h syntax.c syntax.h progname.h progname.c basic-auth.h basic-auth.c fileio.h fileio.c tempfile.h tempfile.c digest-auth.h digest-auth.c crypt-apr1.c crypt-apr1.h generate-salt.c generate-salt.h readpasswd.c readpasswd.h sha.h md5.h openssl-version.h openssl-version.c
