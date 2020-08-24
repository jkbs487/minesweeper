#!/bin/sh

#set -x

PROJECT=minesweeper

make clean
make
echo "*************************start*************************"
./bin/${PROJECT} 
