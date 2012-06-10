if [ $# != 3 ];then
	echo "Usage : $0 mirror arch date"
	exit 1
fi
MIRROR=$1
ARCH=$2
DATE=$3

if [ -e install-$ARCH-minimal.iso ];then
	rm -f install-$ARCH-minimal.iso
fi
if [ -e stage3-$ARCH.tar.bz2 ];then
	rm -f stage3-$ARCH.tar.bz2
fi
if [ -e portage.tar.xz ];then
	rm -f portage.tar.xz
fi

axel -a "$MIRROR/gentoo/releases/$ARCH/current-iso/install-$ARCH-minimal-$DATE.iso"
axel -a "$MIRROR/gentoo/releases/$ARCH/current-iso/stage3-$ARCH-$DATE.tar.bz2"
axel -a "$MIRROR/gentoo/snapshots/portage-latest.tar.xz"

wget -q "$MIRROR/gentoo/releases/$ARCH/current-iso/install-$ARCH-minimal-$DATE.iso.DIGESTS" -O -|grep -A1 "# MD5 HASH" |grep install-$ARCH-minimal-$DATE.iso$ |md5sum -c -
if [ $? = 1 ];then
	echo -e "\e[1;31m"
	read -n 1 -p "install-$ARCH-minimal-$DATE.iso download failed, deleted?[y]" res
	echo -e "\e[0m"
	if [ $res = "y" ];then
		rm -f install-$ARCH-minimal-$DATE.iso
	fi
fi
if [ -e install-$ARCH-minimal-$DATE.iso ];then
	mv -f install-$ARCH-minimal-$DATE.iso install-$ARCH-minimal.iso
fi

wget -q "$MIRROR/gentoo/releases/$ARCH/current-iso/stage3-$ARCH-$DATE.tar.bz2.DIGESTS" -O -|grep -A1 "# MD5 HASH" |grep stage3-$ARCH-$DATE.tar.bz2$ |md5sum -c -
if [ $? = 1 ];then
	echo -e "\e[1;31m"
	read -n 1 -p "stage3-$ARCH-$DATE.tar.bz2 download failed, deleted?[y]" res
	echo -e "\e[0m"
	if [ $res = "y" ];then
		rm -f stage3-$ARCH-$DATE.tar.bz2
	fi
fi
if [ -e stage3-$ARCH-$DATE.tar.bz2 ];then
	mv -f stage3-$ARCH-$DATE.tar.bz2 stage3-$ARCH.tar.bz2
fi

wget -q "$MIRROR/gentoo/snapshots/portage-latest.tar.xz.md5sum" -O -|md5sum -c -
if [ $? = 1 ];then
	echo -e "\e[1;31m"
	read -n 1 -p "portage-latest.tar.xz download failed, deleted?[y]" res
	echo -e "\e[0m"
	if [ $res = "y" ];then
		rm -f portage-latest.tar.xz
	fi
fi
if [ -e portage-latest.tar.xz ];then
	mv -f portage-latest.tar.xz portage.tar.xz
fi
