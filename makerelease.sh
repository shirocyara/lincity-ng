#!/bin/sh
cat data/gui/creditslist.xml |grep -v "@"|cut -d\> -f2|cut -d\< -f1 >AUTHORS
echo "# automatically generated from data/gui/creditslist.xml. Do not edit. #">>AUTHORS

find ./ -name *.o -exec rm {} \;
find ./ -name *.a -exec rm {} \;
find ./ -name *.exe -exec rm {} \;
find ./ -name lincity-ng -type f -exec rm {} \;

./autogen.sh

windres contrib/win32/lincity-ng.rc -O coff -o contrib/win32/lincity-ng.res

./configure
make
