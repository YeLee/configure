#!/bin/bash
intertime=300
if [ -e /tmp/wallpaper ];then
	exit 0
else
	touch /tmp/wallpaper
fi

signal_handle()
{
	rm /tmp/wallpaper
	exit 1
}
trap signal_handle SIGHUP SIGINT SIGQUIT SIGABRT SIGKILL SIGALRM SIGTERM
	
while true
do
	for i in $(find $1 -type f -name "*.png")
	do
		fvwm-root --retain-pixmap $i
		sleep $intertime
		if [ -z $(pgrep fvwm) ];then
			rm /tmp/wallpaper
			exit 0
		fi
	done
done
