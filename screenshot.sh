#!/bin/bash
for((i=10;i>=1;i--));do notify-send -t 800 剩余$i秒…… && sleep 1;done
scrot '%Y-%m-%d_%H%M%S_$wx$h.jpg' -e 'mv $f ~/图片/'
