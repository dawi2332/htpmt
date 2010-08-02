MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST = fct.h

AM_CPPFLAGS = -I$(top_srcdir)
LDADD = $(LIBMD)

if ENABLE_LIBMD
check_PROGRAMS = libmd
TESTS = libmd
endif
