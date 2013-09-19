#!/bin/bash
for i in {10..1};do notify-send -t 800 剩余${i}秒…… && sleep 1;done
scrot '%Y-%m-%d_%H%M%S_$wx$h.jpg' -e 'mv $f ~/图片/'
notify-send -t 5000 截图已保存到\"${HOME}/图片\"下面。

