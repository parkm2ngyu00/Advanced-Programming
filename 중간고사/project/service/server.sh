#!/bin/bash

case "$1" in
	start)
		cd /home/vagrant/project/service/echo; nohup ./service_echo.py > /dev/null 2>&1 &
		cd /home/vagrant/project/service/md5; nohup ./service_md5.py > /dev/null 2>&1 &
		cd /home/vagrant/project/service/sha1; nohup ./service_sha1.py > /dev/null 2>&1 &
		cd /home/vagrant/project/service/sha256; nohup ./service_sha256.py > /dev/null 2>&1 &
		cd /home/vagrant/project/service/sha512; nohup ./service_sha512.py > /dev/null 2>&1 &
		;;
	stop)
		pkill -9 python3
		;;
	*)
		echo "Usage: $0 {start|stop}"
		exit 1
esac

exit 0
