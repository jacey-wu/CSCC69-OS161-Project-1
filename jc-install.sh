#!/bin/bash

# This install file is jacey's peculiar file system

# export PATH=$PATH:/usr/local/cms/toolchain/bin
export PATH=$HOME/csc/c69/tools/usr/local/cms/toolchain/share/mk:$PATH
export MAKESYSPATH=$HOME/csc/c69/tools/usr/local/cms/toolchain/share/mk

cd ./src
./configure --ostree=$HOME/cscc69/root
cd ..

cd src/kern/conf
./config ASST1

cd ../compile/ASST1
bmake depend
bmake

bmake install

cd ../../..
bmake
bmake install

cp ./sys161.conf $HOME/cscc69/root
