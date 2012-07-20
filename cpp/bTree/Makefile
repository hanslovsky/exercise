CC = c++
CFLAGS = -Wall -g
LDFLAGS =

all: bTree

main.o : main.cpp include/bTree.hxx
	$(CC) $(CFLAGS) -c main.cpp

bTree : main.o
	$(CC) $(CFLAGS) main.o $(LDFLAGS) -o bTree

