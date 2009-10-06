#ACLOCAL_AMFLAGS = -I m4
SUBDIRS = contrib libmd src doc man tests
MAINTAINERCLEANFILES = aclocal.m4 configure config.h.in Makefile.in en@quot.po en@boldquot.po version_info.h
EXTRA_DIST = TODO BUGS

# Create ChangeLog on the fly during 'make dist'
dist-hook:
	test -z `which svn` && test -d ${top_srcdir}/.svn || svn log ${top_srcdir} | ${top_srcdir}/contrib/gnuify-changelog  > ${top_distdir}/ChangeLog
