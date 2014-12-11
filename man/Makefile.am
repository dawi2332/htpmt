MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST = htpasswd.txt htpasswd.1 htdigest.txt htdigest.1
DISTCLEANFILES = htpasswd.1 htdigest.1
CLEANFILES = htpasswd.xml htdigest.xml

man1_MANS = htpasswd.1 htdigest.1

SUFFIXES = .1 .txt

# This target will take quite some time or may even fail if
# the DocBook XSL stylesheets are not installed (properly).
.txt.1:
	a2x -f manpage -d manpage $<
