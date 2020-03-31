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

if `elvex --version 2&> /dev/null`;
then
    echo "*** Elvex is already installed on your system.";
    read -r -p "Are you sure to reinstall it? [y/N] " install_resp
    case "$install_resp" in
	[yY][eE][sS]|[yY]) 
            install='true'
            ;;
	*)
            install='false'
            ;;
    esac
else
    install='false'
fi

if [ $install = 'true' ] && [ -d 'Elvex' ];
then
    download='false'
    echo "*** Elvex is already dowloaded onto this directory.";
    read -r -p "Do you want to update it? [y/N] " update_resp
    case "$update_resp" in
	[yY][eE][sS]|[yY])
	    update='true'
            ;;
	*)
	    update='false'
	    ;;
    esac
else
    update='false';
    download='true'
fi

if `git --version 2&> /dev/null`; then
    git='true'
else
    echo "*** git isn't installed on your system.";
    git='false'
fi

$conf='true'
if `g++ --version 2&> /dev/null`; then
    echo "*** g++ isn't installed on your system.";
    conf='false'
    read -r -p "Do you want to update it? [y/N] " conf_resp
    case "$conf_resp" in
	[yY][eE][sS]|[yY])
	    apt-get install g++;
	    conf='true'
            ;;
	*)
	    ;;
    esac
fi

if [ $git = 'true' ] && [ $install = 'true' ] && [ $update = 'true' ]; then
    (cd Elvex; git pull)
fi

if [ $git = 'true' ] && [ $install = 'true' ] && [ $download = 'true' ]; then
    git clone https://github.com/lionelclement/Elvex.git
fi

if [ $install = 'true' ] && `g++ --version 2&> /dev/null` && `bison --version 2&> /dev/null` && `flex --version 2&> /dev/null` && `xml2-config --version 2&> /dev/null` && `aclocal --version 2&> /dev/null` && `automake --version 2&> /dev/null` && `autoconf --version 2&> /dev/null`; then
    (cd Elvex;
     aclocal;
     automake -a;
     autoconf;
     read -r -p "*** By default, elvex will be installed in '/usr/local'. Do you want to specify
an installation prefix other than '/usr/local'? [y/N] " prefix_resp
     case "$prefix_resp" in
	 [yY][eE][sS]|[yY])
	     prefix='/usr/local'
	     read -r -p "Specify installation prefix [/usr/local] " prefix
             ;;
	 *)
	     prefix='/usr/local'
	     ;;
     esac
     echo "Configure..."
     ./configure -q --prefix=$prefix;
     make -j5 -s;
     sudo make install;
     . ./try-me.sh)
fi
