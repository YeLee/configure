#!/bin/bash

declare -A sectip
declare -A msgout

sectip[C]=' seconds remaining...'
sectip[zh_CN]='秒剩余……'
sectip[zh_TW]='秒剩餘……'

msgout[C]='Screenshot saved as: '
msgout[zh_CN]='截图已保存为：'
msgout[zh_TW]='截圖已儲存為：'

USER_DIRS=${XDG_CONFIG_HOME:-~/.config}/user-dirs.dirs
[ -f "$USER_DIRS" ] && source "$USER_DIRS"
[ -d "$XDG_PICTURES_DIR" ] && PIC_DIR="$XDG_PICTURES_DIR" || PIC_DIR="$PWD"

tipstr=${sectip[${LC_MESSAGES%.*}]}
[ -z "${tipstr}" ] && tipstr="${sectip[C]}"
outstr=${msgout[${LC_MESSAGES%.*}]}
[ -z "${outstr}" ] && outstr="${msgout[C]}"

for i in {10..1};do notify-send -t 800 "${i}${tipstr}" && sleep 1;done
scrot '%Y-%m-%d_%H%M%S_$wx$h.jpg' -e "notify-send -t 5000 \"${outstr} ${PIC_DIR}/\$f\" && [ "${PIC_DIR}" == "${PWD}" ] || mv \$f ${PIC_DIR}"

