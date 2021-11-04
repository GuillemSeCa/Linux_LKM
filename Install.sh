#!/bin/bash

sudo apt install raspberrypi-kernel-headers

if [ -d "code" ]; then
    cd code && make clean && make && sudo insmod LKM.ko && cp A.sh /home/pi/A.sh && cp B.sh /home/pi/B.sh && cp C.sh /home/pi/C.sh && cp D.sh /home/pi/D.sh && chmod +x /home/pi/A.sh /home/pi/B.sh /home/pi/C.sh /home/pi/D.sh && cd ..
fi
echo "$(pwd)"
if [ ! -d "code" ]; then
    echo "As the git repo doesn't exist already we clone it!"
    sudo apt-get -y install git && git clone https://github.com/GuillemSeCa/Linux_LKM.git
    cd Linux_LKM/code && make clean && make && sudo insmod LKM.ko && cp A.sh /home/pi/A.sh && cp B.sh /home/pi/B.sh && cp C.sh /home/pi/C.sh && cp D.sh /home/pi/D.sh && chmod +x /home/pi/A.sh /home/pi/B.sh /home/pi/C.sh /home/pi/D.sh
fi
