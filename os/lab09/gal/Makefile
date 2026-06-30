CC = gcc
CFLAGS = -Wall -g

all: main

main: matrix_bench.h matrix_bench.c  main.c
		$(CC) $(CFLAGS)  matrix_bench.c main.c -o main

clean:
		rm -f main