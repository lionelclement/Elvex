#!/bin/bash
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

if test `which elvex`;
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

if [ $install = 'true' ];
then
    if [ -d 'Elvex' ];
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

    if test `which git`; then
	git='true'
    else
	echo "*** git isn't installed on your system.";
	git='false'
    fi
    
    if [ $git = 'true' ] && [ $install = 'true' ] && [ $update = 'true' ]; then
        (cd Elvex; git pull)
    fi
    
    if [ $git = 'true' ] && [ $install = 'true' ] && [ $download = 'true' ]; then
        git clone https://github.com/lionelclement/Elvex.git
    fi

    install_gxx='false'
    if test `which g++`; then
	echo "*** g++ isn't installed on your system.";
	conf='false'
	read -r -p "Do you want to install it? [y/N] " conf_resp
	case "$conf_resp" in
	    [yY][eE][sS]|[yY])
		install_gxx=true;
		;;
	    *)
		;;
	esac
    fi
    
    install_gxx='false'
    if test `which g++`; then
	echo "*** g++ isn't installed on your system.";
	conf='false'
	read -r -p "Do you want to install it? [y/N] " conf_resp
	case "$conf_resp" in
	    [yY][eE][sS]|[yY])
		install_gxx=true;
		;;
	    *)
		;;
	esac
    fi
    install_bison='false'
    if test `which bison`; then
	echo "*** bison isn't installed on your system.";
	conf='false'
	read -r -p "Do you want to install it? [y/N] " conf_resp
	case "$conf_resp" in
	    [yY][eE][sS]|[yY])
		install_bison=true;
		;;
	    *)
		;;
	esac
    fi
    install_flex='false'
    if test `which flex`; then
	echo "*** flex isn't installed on your system.";
	conf='false'
	read -r -p "Do you want to install it? [y/N] " conf_resp
	case "$conf_resp" in
	    [yY][eE][sS]|[yY])
		install_flex=true;
		;;
	    *)
		;;
	esac
    fi
    install_automake='false'
    if test `which automake`; then
	echo "*** automake isn't installed on your system.";
	conf='false'
	read -r -p "Do you want to install it? [y/N] " conf_resp
	case "$conf_resp" in
	    [yY][eE][sS]|[yY])
		install_automake=true;
		;;
	    *)
		;;
	esac
    fi
    install_autoconf='false'
    if test `which autoconf`; then
	echo "*** autoconf isn't installed on your system.";
	conf='false'
	read -r -p "Do you want to install it? [y/N] " conf_resp
	case "$conf_resp" in
	    [yY][eE][sS]|[yY])
		install_autoconf=true;
		;;
	    *)
		;;
	esac
    fi
    install_xml2_config='false'
    if test `which xml2-config`; then
	echo "*** libxml2-dev isn't installed on your system.";
	conf='false'
	read -r -p "Do you want to install it? [y/N] " conf_resp
	case "$conf_resp" in
	    [yY][eE][sS]|[yY])
		install_xml2_config=true;
		;;
	    *)
		;;
	esac
    fi

    if [ $install_gxx = 'true' ] || [ $install_bison = 'true' ] || [ $install_flex = 'true' ] || [ $install_automake = 'true' ] || [ $install_autoconf = 'true' ] ||[ $install_xml2_config = 'true' ];
    then
	echo "apt-get update"
    fi
    if [ $install_gxx = 'true' ];
    then
	echo "apt-get install g++"
    fi
    if [ $install_bison = 'true' ];
    then
	echo "apt-get install bison"
    fi
    if [ $install_flex = 'true' ];
    then
	echo "apt-get install flex"
    fi
    if [ $install_automake = 'true' ];
    then
	echo "apt-get install automake"
    fi
    if [ $install_autoconf = 'true' ];
    then
	echo "apt-get install autoconf"
    fi
    if [ $install_xml2_config = 'true' ];
    then
	echo "apt-get install libxml2-dev"
    fi
# if `bison --version 2&> /dev/null`; then
#     echo "*** bison isn't installed on your system.";
#     conf='false'
#     read -r -p "Do you want to install it? [y/N] " conf_resp
#     case "$conf_resp" in
# 	[yY][eE][sS]|[yY])
# 	    apt-get install bison;
# 	    conf='true'
#             ;;
# 	*)
# 	    ;;
#     esac
# fi

# if [ $install = 'true' ] && `g++ --version 2&> /dev/null` && `bison --version 2&> /dev/null` && `flex --version 2&> /dev/null` && `xml2-config --version 2&> /dev/null` && `aclocal --version 2&> /dev/null` && `automake --version 2&> /dev/null` && `autoconf --version 2&> /dev/null`; then
#     (cd Elvex;
#      aclocal;
#      automake -a;
#      autoconf;
#      read -r -p "*** By default, elvex will be installed in '/usr/local'. Do you want to specify
# an installation prefix other than '/usr/local'? [y/N] " prefix_resp
#      case "$prefix_resp" in
# 	 [yY][eE][sS]|[yY])
# 	     prefix='/usr/local'
# 	     read -r -p "Specify installation prefix [/usr/local] " prefix
#              ;;
# 	 *)
# 	     prefix='/usr/local'
# 	     ;;
#      esac
#      echo "Configure..."
#      ./configure -q --prefix=$prefix;
#      make -j5 -s;
#      sudo make install;
#      . ./try-me.sh)
# fi

fi
