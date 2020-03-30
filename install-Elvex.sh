#!/bin/sh
# ##################################################
#
# ELVEX
#
# Copyright 2019 LABRI, 
# CNRS (UMR 5800), the University of Bordeaux,
# and the Bordeaux INP
#
# Author: 
# Lionel Clément
# LaBRI -- Université Bordeaux 
# 351, cours de la Libération
# 33405 Talence Cedex - France
# lionel.clement@labri.fr
# 
# This file is part of ELVEX.
#
################################################## #

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
. ./try-me.sh
cd ..
