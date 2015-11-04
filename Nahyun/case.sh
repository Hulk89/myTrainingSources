#!/bin/sh
# usage : ./case.sh fileName #ofURLinFile

echo Hello Nahyun

FILENAME=$1
NUMURL=`cat "$FILENAME" | wc -l`
count=0

RANDNUM=$[ $RANDOM % $NUMURL + 1 ]


cat $FILENAME | while read LINE
do
	if test $count -eq $RANDNUM
	then
		open "$LINE"
		break
	fi
	count=`expr $count + 1`
done

