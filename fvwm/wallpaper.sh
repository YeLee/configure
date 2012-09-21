#!/bin/bash
intertime=300
if [ -e /tmp/wallpaper ];then
	exit 0
else
	touch /tmp/wallpaper
fi
while true
do
	for i in $(find $1 -type f -name "*.png")
	do
		fvwm-root --retain-pixmap $i
		sleep $intertime
		if [ -z $(pgrep fvwm) ];then
			exit 0
			rm -f /tmp/wallpaper
		fi
	done
done
