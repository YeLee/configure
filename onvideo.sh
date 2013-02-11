#!/bin/bash
#修改自funicorn的脚本，对其功能进行了一些简化。
#原脚本来自http://forum.ubuntu.org.cn/viewtopic.php?f=73&t=344921
#参数1为在线视频的地址。
#参数2为视频画质，可以为normal，high，super或real。
szurl=$1
szdefinition=$2
if [ $# -gt 2 ];then
	echo "$0 url definition"
	exit 1
fi
USERAGENT="Mozilla/5.0"
szparser="http://www.flvcd.com/parse.php?kw=$szurl&format=$szdefinition"
echo $szparser

wget -q --user-agent="$USERAGENT" "$szparser" -O - |\
egrep -i "<br>|d_clip_button" |grep -o '\"http[^"]*\"' |tr -d '"' |\
mplayer2 -user-agent "$USERAGENT" -playlist -
