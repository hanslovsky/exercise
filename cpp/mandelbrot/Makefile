CC = c++
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lvigraimpex -lparser -lcomplex

all: mandelbrot

mandelbrot.o: src/mandelbrot.cpp include/complex.hxx include/mandelbrot.hxx
	$(CC) $(CFLAGS) -c src/mandelbrot.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

mandelbrot: main.o mandelbrot.o
	$(CC) $(CLAGS) mandelbrot.o main.o $(LDFLAGS) -o mandelbrot