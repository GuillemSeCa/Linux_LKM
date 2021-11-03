#!/bin/bash

sudo apt install raspberrypi-kernel-headers

if [ ! -d "Linux_LKM" ]; then
    echo "As the git repo doesn't exist already we clone it!"
    sudo apt-get -y install git && git clone https://github.com/GuillemSeCa/Linux_LKM.git
fi

cd Linux_LKM && make clean && make && sudo insmod LKM.ko && cp A.sh /home/pi/A.sh && cp B.sh /home/pi/B.sh && cp C.sh /home/pi/C.sh && cp D.sh /home/pi/D.sh