#!/bin/bash

# This install file is jacey's peculiar file system

export PATH=$PATH:/usr/local/cms/toolchain/bin

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

bmake install

cp ./sys161.conf $HOME/cscc69/root
