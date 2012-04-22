if [ ! -d /dev/shm/firefox ]; then
	mkdir /dev/shm/firefox
	pwd
	cd ~/.mozilla/firefox/*.default
	pwd
	cp -a * /dev/shm/firefox
	cd -
fi
firefox -P shm