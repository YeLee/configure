#!/bin/bash
i=0
if [ $# != 2 ] ;then
	echo "Usage : $0 directory playlist"
	exit 1
fi

if [ ! -d $1 ] ;then
	echo "$1 is an invalid directory."
	exit 1
fi
touch $2
if [ $? -ne 0 ] ;then
	exit 1
fi
echo "[playlist]" >$2

find $1 -type f -iname "*.mp3" |\
while read fmp
do
	i=$( expr $i + 1 )
	echo File${i}=${fmp} >>$2
done

i=$( tail -n1 $2 |grep -o '[0-9]\+' |head -n1 )
sed -i "2 i\NumberOfEntries=$i" $2
echo "$2 created success."
