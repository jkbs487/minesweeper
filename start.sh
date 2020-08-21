#!/bin/sh

#set -x

PROJECT=minesweeper

make clean
make
./bin/${PROJECT}
