#!/bin/bash
intertime=3600
session=/tmp/wallpaper
if [ -e $session  ];then
	exit 0
else
	touch $session
fi

signal_handle()
{
	rm $session
	exit 1
}
trap signal_handle SIGHUP SIGINT SIGQUIT SIGABRT SIGKILL SIGALRM SIGTERM

index=0

declare -a wallpaper
genwallpaper()
{
	for i in "${1}"/*.png
	do
		wallpaper[index]="${i##*/}"
		let "index++"
	done
}

genramnum()
{
	ramnum=$(($RANDOM%${#wallpaper[@]}))
	[ "$ramnum" -eq "$1" ] && genramnum $1
	return $ramnum
}

genwallpaper "$1"
index=$((${#wallpaper[@]}+1))

while true
do
	genramnum $index
	index=$?
	echo ${1}/${wallpaper[index]}
	fvwm-root --retain-pixmap ${1}/${wallpaper[index]}
	sleep $intertime
	if [ -z $(pgrep fvwm) ];then
		rm $session
		exit 0
	fi
done

