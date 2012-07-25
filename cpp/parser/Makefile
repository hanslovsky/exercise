CC = c++
CFLAGS = -Wall -g -Iinclude
LDFLAGS =

all: parse libparser.so

install:
	cp include/parser.hxx $(HOME)/local/include/own
	cp libparser.so $(HOME)/local/lib

libparser.so: parser.o
	$(CC) -shared -o libparser.so parser.o

parser.o: src/parser.cpp include/parser.hxx
	$(CC) $(CFLAGS) -fPIC -c src/parser.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

parse: main.o parser.o
	$(CC) $(CLAGS) parser.o main.o $(LDFLAGS) -o parse