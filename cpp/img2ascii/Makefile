CC = c++
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lvigraimpex

all: img2ascii

img2ascii: main.o
	$(CC) $(CFLAGS) img2ascii.o main.o $(LDFLAGS) -o img2ascii

img2ascii.o: src/img2ascii.cpp
	$(CC) $(CFLAGS) -c src/img2ascii.cpp

main.o: main.cpp img2ascii.o
	$(CC) $(CFLAGS) -c main.cpp

clean: