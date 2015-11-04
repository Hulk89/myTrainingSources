#!/bin/sh

rm -rf cscope.files cscope.out tags
find $PWD/. \( -name '*.c' -o -name '*.cpp' -o -name '*.cc' -o -name '*.h' -o -name '*.s' -o -name '*.S' \) -print > cscope.files
cscope -bq
ctags -L cscope.files -f tags
cscope -i cscope.files
