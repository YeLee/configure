#!/bin/bash
[ $# -gt 0 ] || echo "Usage : $0 procname"
while [ $# -gt 0 ]
do
	for i in $(pgrep -f $1)
	do
		[ $i -eq $$ ] && continue
		kill -TERM $i
	done
	shift
done

