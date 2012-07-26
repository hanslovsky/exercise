CC = c++
CFLAGS = -Wall -g -Iinclude
LDFLAGS =

all: libcomplex.so

install:
	cp include/complex.hxx $(HOME)/local/include/own
	cp libcomplex.so $(HOME)/local/lib

libcomplex.so: complex.o
	$(CC) -shared -o libcomplex.so complex.o

complex.o: src/complex.cpp include/complex.hxx
	$(CC) $(CFLAGS) -fPIC -c src/complex.cpp