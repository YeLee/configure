#!/bin/bash
if [ $# != 3 ];then
	echo "Usage : $0 url protocol Ext-filename"
	exit 1
fi
wget --quie --user-agent="Mozilla/5.0" $1 -O -|grep $2|sed "s/\($2\)/\n\1/g"|grep "\.$3"|sed "s/\($3\)/\1\n/g"|egrep -i "^$2|$3$"|xargs -n1 -iargs wget --user-agent="Mozilla/5.0" --tries=1 --directory-prefix=./$3 "args"