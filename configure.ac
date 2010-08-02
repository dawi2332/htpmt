#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([htpmt], [1.0], [http://code.google.com/p/htpmt/issues/entry], [htpmt], [http://code.google.com/p/htpmt/])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([gnits])
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

AC_CHECK_DECLS([[P_tmpdir], [__progname]])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([strerror mktemp mkstemp mkstemps tcsetattr atexit random srandom srandomdev rand srand err errx warn warnx])

AC_ARG_WITH([openssl],
	    [AS_HELP_STRING([--with-openssl],
			    [build with support for OpenSSL])],
	    [with_builtin_libmd="no"],
	    [with_openssl=no])

AC_ARG_WITH([builtin-libmd],
	      [AS_HELP_STRING([--without-builtin-libmd],
			      [build without the built-in libmd])],
	      [with_openssl=yes],
	      [with_builtin_libmd=yes])

LIBCRYPTO=
AS_IF([test "x$with_openssl" != xno],
      [AC_CHECK_LIB([crypto], [MD5_Init],
		    [AC_SUBST([LIBCRYPTO], ["-lcrypto"])
		    AC_DEFINE([HAVE_LIBCRYPTO], [1],
			      [Define if you have libcrypto])
		    AC_MSG_NOTICE([Using OpenSSL for cryptographic hash functions])
		    ],
		    [AC_MSG_FAILURE([--with-openssl was given, but test for libcrypto failed])], [])])

LIBMD=
AS_IF([test "x$with_builtin_libmd" != xno],
      [AC_SUBST([LIBMD], ["\$(top_builddir)/lib/md/libmd.a"])
      AC_DEFINE([HAVE_LIBMD], [1],
		[Define if you have libmd])
      AC_MSG_NOTICE([Using libmd (built-in) for cryptographic hash functions])])

AM_CONDITIONAL([ENABLE_LIBMD], [test "x$with_builtin_libmd" != xno])

AC_CONFIG_FILES([
		 Makefile 
		build-aux/Makefile 
		src/Makefile 
		contrib/Makefile 
		man/Makefile 
		doc/Makefile 
		lib/Makefile 
		lib/md/Makefile 
		lib/md/tests/Makefile 
		lib/htpmt/Makefile
		tests/Makefile
]) 



AC_OUTPUT
