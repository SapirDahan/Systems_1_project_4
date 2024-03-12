CC = gcc
CFLAGS = -Wall

.PHONY: all clean

all: digitcompress

digitcompress: encodemain.o compress.o
	$(CC) $(CFLAGS) -o digitcompress encodemain.o compress.o

encodemain.o: encodemain.c compress.h
	$(CC) $(CFLAGS) -c encodemain.c -o encodemain.o

compress.o: compress.c compress.h
	$(CC) $(CFLAGS) -c compress.c -o compress.o

clean:
	rm -f *.o digitcompress