#!/bin/sh
cat data/gui/creditslist.xml |grep -v "@"|cut -d\> -f2|cut -d\< -f1 >AUTHORS
echo "# automatically generated from data/gui/creditslist.xml. Do not edit. #">>AUTHORS

find ./ -name *.o | xargs rm
find ./ -name *.a | xargs rm
./autogen.sh
./configure
make
