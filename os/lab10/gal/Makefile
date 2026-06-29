CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: main

main: buffer_sync.h buffer_sync.c  main.c
		$(CC) $(CFLAGS)  buffer_sync.c main.c -o main

clean:
		rm -f main