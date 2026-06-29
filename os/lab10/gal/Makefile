CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: main

main: main.c buffer_sync.c  buffer_sync.h
		$(CC) $(CFLAGS) main.c buffer_sync.c -o main

clean:
		rm -f main