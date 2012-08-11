CC = c++
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lvigraimpex -lparser -lcomplex

all: mandelbrot

build: libmandelbrot.so

install: build
	cp include/mandelbrot.hxx $(HOME)/local/include/own
	cp libmandelbrot.so $(HOME)/local/lib

libmandelbrot.so: mandelbrot.o
	$(CC) -shared -o libmandelbrot.so mandelbrot.o -lcomplex -lvigraimpex

mandelbrot.o: src/mandelbrot.cpp include/complex.hxx include/mandelbrot.hxx
	$(CC) $(CFLAGS) -fPIC -c src/mandelbrot.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

mandelbrot: main.o mandelbrot.o
	$(CC) $(CLAGS) mandelbrot.o main.o $(LDFLAGS) -o mandelbrot

clean:
	rm libmandelbrot.so mandelbrot.o