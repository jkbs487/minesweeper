PWD = $(shell pwd)
CC = g++
CFLAGS += -g 
CFLAGS += -I$(PWD)/../include
OBJS = 

default: build

build:
	$(MAKE) -C src

.PHONY: clean

clean:
	$(MAKE) -C src clean
