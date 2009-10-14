MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST = htpasswd.txt htpasswd.1 htdigest.txt htdigest.1
DISTCLEANFILES = htpasswd.1 htdigest.1
CLEANFILES = htpasswd.xml htdigest.xml

man1_MANS = htpasswd.1 htdigest.1

# if one of those fails because xsltproc can't load the XSL stylesheet
# check whether the docbook-xsl package is installed and XML_CATALOG_FILES is
# is set and points to a valid catalog file
htpasswd.1: htpasswd.txt
	a2x -L --xsltproc-opts="--novalid" -f manpage -d manpage $<

htdigest.1: htdigest.txt
	a2x -L --xsltproc-opts="--novalid" -f manpage -d manpage $<
