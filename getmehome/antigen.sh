#!/bin/sh

set -ex
if test -f Makefile; then
  make distclean
fi
rm -f *.tar.* *.tgz
rm -Rf autom4te.cache
rm -f Makefile.in aclocal.m4 configure depcomp install-sh missing ltmain.sh config.guess config.sub config.h.in mkinstalldirs INSTALL
