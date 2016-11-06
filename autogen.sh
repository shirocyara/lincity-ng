#!/bin/sh

# Correct working directory?
if test ! -f configure.ac ; then
  echo "*** Please invoke this script from directory containing configure.ac."
  exit 1
fi

echo aclocal
aclocal
echo autoheader
autoheader
echo automake --add-missing --copy
automake --add-missing --copy
echo autoconf
autoconf

