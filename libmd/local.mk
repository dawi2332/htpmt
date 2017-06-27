if ENABLE_LIBMD
noinst_LIBRARIES += libmd.a
endif

libmd_a_SOURCES = libmd/md5.h \
		  libmd/md5c.c \
		  libmd/sha1c.c \
		  libmd/sha_locl.h \
		  libmd/sha.h

# vim:ft=automake
