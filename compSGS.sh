#!/bin/bash
read -p "请输目标目录：" SGS_INSTALLDIR
if [ -z $SGS_INSTALLDIR ] ;then
  echo "输入为空，正在退出。" 
  exit 1
fi
export CPLUS_INCLUDE_PATH=$PWD/dev-lib/include
export LIBRARY_PATH=$PWD/dev-lib/libs
export LD_LIBRARY_PATH=$PWD/dev-lib/libs
qmake QSanguosha.pro
make
lrelease QSanguosha.pro
mkdir -p $SGS_INSTALLDIR
cp -R {lib,font,doc,audio,diy,etc,extension-doc,QSanguosha,qt_zh_CN.qm,backdrop,image,lang,scenarios,lua,sanguosha.qm,sanguosha.qss,qsanguosha.sh,dev-lib/libs} $SGS_INSTALLDIR
