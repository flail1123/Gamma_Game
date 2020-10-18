CC = gcc
CFLAGS = -Wall -Wextra 
LDFLAGS = 

.PHONY: all clean

all: main

main: main.o request.o print.o del.o add.o check.o struct.o
	$(CC) $(LDFLAGS) -o $@ $^

request.o: request.c request.h add.h del.h check.h print.h struct.h
	$(CC) $(CFLAGS) -c $<

print.o: print.c print.h struct.h
	$(CC) $(CFLAGS) -c $<

del.o: del.c del.h struct.h
	$(CC) $(CFLAGS) -c $<

check.o: check.c check.h struct.h
	$(CC) $(CFLAGS) -c $<

add.o: add.c add.h struct.h
	$(CC) $(CFLAGS) -c $<

struct.o: struct.c struct.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c request.h del.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm main.o 
	rm request.o 
	rm print.o
	rm del.o
	rm check.o
	rm add.o
	rm struct.o
	
