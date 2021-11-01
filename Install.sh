#!/bin/bash

sudo apt install raspberrypi-kernel-headers

if [ ! -d "Linux_LKM" ]; then
    echo "As the git repo doesn't exist already we clone it!"
    sudo apt-get install git && git clone https://github.com/GuillemSeCa/Linux_LKM.git
fi

cd Linux_LKM && make clean && make && sudo insmod LKM.ko
