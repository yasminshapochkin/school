CC = gcc
CFLAGS = -Wall -g

all: main

main: buffer_sync.h buffer_sync.c  main.c
		$(CC) $(CFLAGS)  buffer_sync.c main.c -o main

clean:
		rm -f main