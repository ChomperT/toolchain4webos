WebOS Toolchain
=========================================

Information
-----------

Toolchains for WebOS && any armv7-linux

How to use?
-----------------

command:
	git clone git://github.com/ChomperT/toolchain4webos
	cd /opt	
	sudo ln -s $DOWNLOAD_PATH/toolchain4webos/CC CC
	export PATH=$PATH:/opt/CC/bin

	arm-linux-gnueabi-gcc hello.c

by Chomper
