CC = c++
CFLAGS = -Wall -g
LDFLAGS = -lpng

all: readimage

readimage: main.o PNGImage.o
	$(CC) $(CFLAGS) PNGImage.o main.o $(LDFLAGS) -o readimage

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

PNGImage.o: src/PNGImage.cpp include/PNGImage.hxx
	$(CC) $(CFLAGS) -c src/PNGImage.cpp
