# About htpmt
htpmt is a suite of tools for managing HTTP authentication files
that are used by web servers to authenticate users. Currently htpmt
includes tools for Basic and Digest HTTP authentication; they are
designed to be a drop-in replacement for the htpasswd and htdigest
tools that come with Apache httpd.

htpmt is distributed under the terms of the Simplified BSD License
(see COPYING for more information).

A quick overview of htpmt htpasswd & htdigest features:
 * crypt(), SHA-1 and MD5 (aka APR1, a Crypt-MD5 variant) encryption
 of passwords for use with HTTP Basic Authentication
 * MD5 encryption of passwords for use with HTTP Digest Authentication
 * add, update & delete user records
 * output to file or stdout
 * password input from tty, command line (only htpasswd) or stdin
 * uses /dev/random for salt generation when available
 * exit codes and command line options conform with Apache
 htpasswd/htdigest
 * utilizes the built-in libmd library or OpenSSL for SHA-1 and MD5
  message digests

# Requirements
The requirements depend on your system's operating system and whether you want to build a release or a development version of htpmt.

Linux, BSD and Mac OS X systems may already meet the requirements, or require the installation of  a few additional software packages from the installation media or the internet.
Windows systems are almost guaranteed to lack all of them, it may even be impossible to find a Windows port for some of them.

## Release
This requires:
  * a working compiler toolchain (i.e. compiler, linker, etc.)
  * GNU make or a compatible make
  * a Bourne-compatible shell (e.g. bash)
  * an implementation of the crypt library function (usually comes with libc)

## Development
In addition to the above, building the trunk or a development branch may require:
  * GNU autotools (automake, autoconf, etc.)
  * GNU m4
  * Perl
  * for manpages and documentation:
    * [AsciiDoc](http://www.methods.co.nz/asciidoc/)
    * fop
    * docbook-xsl
    * libxslt
    * libxml2

# Building
If you want to build a development version, you need to generate configure and the Makefiles from their respective sources:
```
autoreconf
```
If not, you can skip directly to building and installing htpmt.
```
./configure
make
make install
```

In order to use OpenSSL instead of the built-in libmd for message digests, run the configure script with the option '--with-openssl':
```
./configure --with-openssl
```

See the file INSTALL for more information.

# Running the test suite
htpmt comes with a suite of unit and regression tests. You can run it with the command
```
make check
```
