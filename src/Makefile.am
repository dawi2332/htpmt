MAINTAINERCLEANFILES = Makefile.in
AM_CPPFLAGS = -I$(top_srcdir)/libmd/
LDADD = libhtcore.a $(top_builddir)/libmd/libmd.a

bin_PROGRAMS = htpasswd htdigest #htconvert
noinst_LIBRARIES = libhtcore.a

libhtcore_a_SOURCES = system.h error.h error.c getpass.c getpass.h basic-auth.h basic-auth.c fileio.h fileio.c tempfile.h tempfile.c digest-auth.h digest-auth.c crypt-apr1.c crypt-apr1.h generate-salt.c generate-salt.h
libhtcore_a_DEPENDENCIES = $(top_builddir)/libmd/libmd.a
