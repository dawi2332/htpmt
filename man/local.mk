man1_MANS = man/htpasswd.1 man/htdigest.1

EXTRA_DIST += $(man1_MANS)
DISTCLEANFILES += $(man1_MANS)
CLEANFILES += htpasswd.xml htdigest.xml

SUFFIXES = .1 .txt

# This target will take quite some time or may even fail if
# the DocBook XSL stylesheets are not installed (properly).
.txt.1:
	$(AM_V_GEN)$(MKDIR_P) $(@D)
	a2x -f manpage -d manpage $<

# vim:ft=automake
