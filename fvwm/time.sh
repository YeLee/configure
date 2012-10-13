#!/bin/bash
for((i=10;i>=1;i--))
do 
notify-send -t 1000 -i "$FVWM_ICON/time.png"  "$(date +現在是%Z時間%n%Y年%m月%d日第%U周%A%n%p%H時%M分%S秒)"
sleep 1
done
