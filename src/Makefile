PWD = $(shell pwd)
CC = g++
CFLAGS += -g 
CFLAGS += -I$(PWD)/../include
PROJECT = ../bin/minesweeper
OBJS =  minesweeper.o

all: $(OBJS) $(PROJECT)

OBJ_DIR = $(PWD)/../objs

$(PROJECT): 
	$(CC) -o $@ $(OBJS) $(LFLAGS) 

$(OBJS): %.o: %.cc
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	-rm *.o $(PROJECT)

