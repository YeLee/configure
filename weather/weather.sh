#!/bin/bash
CITYCODE=101280802
#http://wap.weather.com.cn/wap
#先用上面的链接查询城市代码
wget http://wap.weather.com.cn/wap/weather/$CITYCODE.shtml -q -O -|egrep -B1 -e ℃  -e strong -e 发布 |egrep -v "\-\-|div"|sed -e 's/<[^>]*>//g' -e 's/\(^[0-9]*\)-\([0-9]*\)-\([0-9]*\)/\1年\2月\3日/g' -e 's/[[:space:]]//g'|sed -e '$!N;s/\n/ /' -e 's/ \([^x00-xff]*\)\([0-9]*℃\/[0-9]*℃\)&nbsp;\([^x00-xff]*\)/ \t\3 \t\2 \t\1/g' -e 's/℃/℃ /g'
