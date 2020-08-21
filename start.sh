#!/bin/sh

#set -x

if [ $# -ne 2 ]; then
	echo "Usage: $0 length width"
	exit 1
fi

PROJECT=minesweeper
LENGTH=$1
WIDTH=$2

make clean
make
echo "----------------start-------------------"
./bin/${PROJECT} ${LENGTH} ${WIDTH}
