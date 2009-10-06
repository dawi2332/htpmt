MAINTAINERCLEANFILES = Makefile.in htpasswd.1 htpasswd.xml htdigest.1 htdigest.xml
EXTRA_DIST = htpasswd.txt htpasswd.1 htdigest.txt htdigest.1
CLEANFILES = htpasswd.1.xml htdigest.1.xml

man1_MANS = htpasswd.1 htdigest.1

# if one of those fails because xsltproc can't load the XSL stylesheet
# check whether the docbook-xsl package is installed and XML_CATALOG_FILES is
# is set and points to a valid catalog file
htpasswd.1: htpasswd.txt
	a2x -L --xsltproc-opts="--novalid" -f manpage -d manpage $<

htdigest.1: htdigest.txt
	a2x -L --xsltproc-opts="--novalid" -f manpage -d manpage $<
