#!/bin/bash

sudo apt install raspberrypi-kernel-headers

if [ ! -d "Linux_LKM" ]; then
    echo "As the git repo doesn't exist already we clone it!"
    sudo apt-get -y install git && git clone https://github.com/GuillemSeCa/Linux_LKM.git
fi

cd code && make clean && make && sudo insmod LKM.ko && cp code/A.sh /home/pi/A.sh && cp code/B.sh /home/pi/B.sh && cp code/C.sh /home/pi/C.sh && cp code/D.sh /home/pi/D.sh && chmod +x /home/pi/A.sh /home/pi/B.sh /home/pi/C.sh /home/pi/D.sh