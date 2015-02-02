mkdir $HOME/cscc69/root

cd $HOME/cscc69/src
./configure --ostree=$HOME/cscc69/root
cd ..

export PATH=$PATH:/usr/local/cms/toolchain/bin

ctags -R --extra=+f --links=no ./src/

cd src/kern/conf
./config ASST1

cd ../compile/ASST1
bmake depend
bmake

bmake install
if [ $? -ne 0 ]; then
	bmake clean
	exit 1
fi

cd ../../..
bmake
bmake install

bmake install
if [ $? -ne 0 ]; then
	bmake clean
	exit 1
fi

cp sys161.conf ../root/