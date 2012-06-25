#!/bin/bash
if [ $# != 1 ];then
	echo "Usage : $0 protaddr"
	exit 1
fi

if [ "$(echo $1|grep -i "^thunder:\/\/")" ];then
	echo $1|sed "s/^thunder:\/\///i"|base64 -d|sed -e 's/^AA//i' -e 's/ZZ$//i'
	echo
	exit 0
fi

if [ "$(echo $1|grep -i "^flashget:\/\/")" ];then
	echo $1|sed -e "s/^flashget:\/\///i" -e "s/&\w*$//g"|base64 -d|sed -e 's/^\[FLASHGET\]//' -e 's/\[FLASHGET\]$//'
	echo
	exit 0
fi

if [ "$(echo $1|grep -i "^qqdl:\/\/")" ];then
	echo $1|sed "s/^qqdl:\/\///i"|base64 -d
	echo
	exit 0
fi

if [ "$(echo $1|grep -i "^fs2you:\/\/")" ];then
	echo $1|sed "s/^fs2you:\/\///i"|base64 -d|sed -e 's/^/http:\/\//' -e 's/|[0-9]*$//'
	echo
	exit 0
fi

 echo -e "\e[1;31mError!Can not be decrypted.\e[0m"
