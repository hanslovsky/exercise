CC = c++
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lopencv_core -lopencv_imgproc -lopencv_highgui

all: img2ascii

img2ascii: main.o
	$(CC) $(CFLAGS) img2ascii.o main.o $(LDFLAGS) -o img2ascii

img2ascii.o: src/img2ascii.cpp include/img2ascii.hxx
	$(CC) $(CFLAGS) -c src/img2ascii.cpp

main.o: main.cpp img2ascii.o
	$(CC) $(CFLAGS) -c main.cpp

clean: