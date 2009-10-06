noinst_LIBRARIES = libmd.a
libmd_a_SOURCES = md5.h md5c.c md5hl.c sha1c.c sha1hl.c sha_locl.h sha.h
nodist_libmd_a_SOURCES = md5hl.c sha1hl.c
noinst_man3_MANS = sha.3 md5.3
EXTRA_DIST = md5.copyright Makefile.orig mdXhl.c mdX.3 README
DISTCLEANFILES = md5hl.c sha0hl.c sha1hl.c
MAINTAINERCLEANFILES = Makefile.in

md5hl.c: mdXhl.c
	(echo '#define LENGTH 16'; \
		sed -e 's/mdX/md5/g' -e 's/MDX/MD5/g' $<) > $@
# sha0hl.c: mdXhl.c
# 	(echo '#define LENGTH 20'; \
# 		sed -e 's/mdX/sha/g' -e 's/MDX/SHA_/g' -e 's/SHA__/SHA_/g' \
# 		$<) > $@

sha1hl.c: mdXhl.c
	(echo '#define LENGTH 20'; \
		sed -e 's/mdX/sha/g' -e 's/MDX/SHA1_/g' -e 's/SHA1__/SHA1_/g' \
		$<) > $@

md5.3: mdX.3
	sed -e "s/mdX/md5/g" -e "s/MDX/MD5/g" $< > $@
	cat md5.copyright >> $@
