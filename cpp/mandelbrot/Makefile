CC = c++
CFLAGS = -Wall -g
LDFLAGS =

all: mandelbrot

complex.o: src/complex.cpp include/complex.hxx
	$(CC) $(CFLAGS) -c src/complex.cpp

mandelbrot.o: src/mandelbrot.cpp include/complex.hxx include/mandelbrot.hxx
	$(CC) $(CFLAGS) -c src/mandelbrot.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

mandelbrot: main.o complex.o mandelbrot.o
	$(CC) $(CLAGS) complex.o mandelbrot.o main.o $(LDFLAGS) -o mandelbrot