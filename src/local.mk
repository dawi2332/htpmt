bin_PROGRAMS = htpasswd htdigest

BASIC_AUTH_SRC = src/basic-auth.c \
		 src/basic-auth.h \
		 src/sha.h \
		 src/md5.h \
		 src/generate-salt.c \
		 src/generate-salt.h \
		 src/crypt-apr1.c \
		 src/crypt-apr1.h

htpasswd_SOURCES = src/htpasswd.c \
		   src/fileio.c \
		   src/fileio.h \
		   src/openssl-version.c \
		   src/openssl-version.h \
		   src/progname.c \
		   src/progname.h \
		   src/readpasswd.c \
		   src/readpasswd.h \
		   src/syntax.c \
		   src/syntax.h \
		   src/tempfile.c \
		   src/tempfile.h \
		   src/system.h

htpasswd_SOURCES += $(BASIC_AUTH_SRC)

DIGEST_AUTH_SRC = src/digest-auth.c \
		  src/digest-auth.h \
		  src/md5.h

htdigest_SOURCES = src/htdigest.c \
		   src/fileio.c \
		   src/fileio.h \
		   src/openssl-version.c \
		   src/openssl-version.h \
		   src/progname.c \
		   src/progname.h \
		   src/readpasswd.c \
		   src/readpasswd.h \
		   src/syntax.c \
		   src/syntax.h \
		   src/tempfile.c \
		   src/tempfile.h \
		   src/system.h

htdigest_SOURCES += $(DIGEST_AUTH_SRC)

LDADD += $(LIBMD) $(LIBCRYPTO)

# vim:ft=automake
