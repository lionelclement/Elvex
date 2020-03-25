#!/bin/sh

sudo apt-get update
sudo apt-get install -y git bison flex libxml2-dev autoconf
apt-get autoclean
if [ ! -d "Elvex" ]; then
    git clone https://github.com/lionelclement/Elvex.git
fi
cd Elvex
aclocal
automake -af
autoconf
./configure
make
sudo make install
cd ..
