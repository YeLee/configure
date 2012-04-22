if [ ! -d /dev/shm/firefox ]; then
	mkdir /dev/shm/firefox
	cp -a ~/.mozilla/firefox/*.default/* /dev/shm/firefox
fi
firefox -P shm