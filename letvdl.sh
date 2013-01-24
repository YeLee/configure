#!/bin/bash
tvid=73868
iformat=high
ipart=76

i=$(ls *.flv.st|sed 's/\([0-9]*\).flv.st/\1/g')
[ -z $i ] && i=1

while [ $i -le $ipart ]
do
	echo "Start the download Episode $i ..."
	wget -q --user-agent="Mozilla/5.0" "http://www.flvcd.com/parse.php?kw=http://www.letv.com/ptv/pplay/$tvid/$i.html&format=$iformat" -O - |grep clipurl |grep -o 'http[^"]*' |axel - --user-agent="Mozilla/5.0" -o $i.flv
	let "i+=1"
done

