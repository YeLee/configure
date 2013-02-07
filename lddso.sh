#!/bin/bash
if [ $# -ne 2 ]
then
	echo "Usage:$0 ELF sopath"
	exit 1
fi
[ -d "$(dirname $1)/lib" ] || mkdir "$(dirname $1)/lib"
for i in $( ldd "$1" |grep "not found" |sed -e 's/^\s*//g' -e 's/\s=>.*//g' )
do
	cp -H "$2/$i" "$(dirname $1)/lib"
	ls $2/$i
done

