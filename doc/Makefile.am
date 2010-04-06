MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST = manual.txt manual.html

manual.html: manual.txt
	asciidoc -b xhtml11 $<

all-local: manual.html
