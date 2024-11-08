#!/bin/bash
cd library
apt download libncurses-dev
filename=$(apt-cache show libncurses-dev | grep Filename | head -n 1 | rev | cut -d '/' -f 1 | rev)
dpkg -x $filename ncurses
cd readline
./configure LDFLAGS="-lncurses -L $(pwd)/../ncurses/usr/lib/x86_64-linux-gnu" CFLAGS="-I $(pwd)/../ncurses/usr/include"
make
make install prefix=`pwd`/../libs
cd ../..
g++ src/duipai.cpp -I ./library/libs/include -I ./library/carefree -L ./library/libs/lib -L ./library/ncurses/usr/lib/x86_64-linux-gnu -lreadline -std=c++17 -lncurses -pthread -o duipai
