CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: main

main: main.c pipeline.c  pipeline.h
		$(CC) $(CFLAGS) main.c pipeline.c -o main

clean:
		rm -f main