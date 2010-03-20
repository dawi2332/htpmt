#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([htpmt], [1.0], [http://code.google.com/p/htpmt/issues/entry], [htpmt], [http://code.google.com/p/htpmt/])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([gnits color-tests])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_RANLIB

# Checks for libraries.
AC_SEARCH_LIBS([crypt], [crypt])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h getopt.h gettext.h termios.h termio.h signal.h endian.h machine/endian.h errno.h crypt.h err.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T

AC_CHECK_DECLS([P_tmpdir])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([strerror mktemp mkstemp mkstemps tcsetattr atexit random srandom srandomdev rand srand err errx warn warnx])
AC_CONFIG_FILES([Makefile build-aux/Makefile src/Makefile contrib/Makefile man/Makefile doc/Makefile libmd/Makefile tests/Makefile]) 

AC_OUTPUT
