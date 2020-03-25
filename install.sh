#!/bin/sh

if [ ! -d "Elvex" ]; then
    apt-get update
    apt-get install -y git bison flex libxml2-dev autoconf
    apt-get autoclean
    https://github.com/lionelclement/Elvex.git
    cd Elvex
    aclocal
    automake -af
    autoconf
    ./configure
    make
    sudo make install
    cd ..
fi
