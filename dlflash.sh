#!/bin/bash
if [ -f ~/.mozilla/plugins/libflashplayer.so ]; 
then
	exit 1
fi

tempdir=$(mktemp -d)
OS_BIT=32

if [ $(uname -m) = "x86_64" ];
then
	let "OS_BIT*=2"
fi

wget -q --user-agent="Mozilla/5.0" "http://get.adobe.com/cn/flashplayer/completion/?installer=Flash_Player_11.2_for_other_Linux_(.tar.gz)_$OS_BIT-bit" -O - |grep -o "http.*tar.gz" |axel - -o $tempdir/install_flash_player_11_linux.tar.gz
tar xf $tempdir/install_flash_player_11_linux.tar.gz -C $tempdir
mkdir -p ~/.mozilla/plugins
cp $tempdir/libflashplayer.so ~/.mozilla/plugins 
rm -rf $tempdir
