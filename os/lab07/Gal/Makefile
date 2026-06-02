CC = gcc
CFLAGS = -Wall -g

all: main

main: vmem_nru.h vmem_nru.c  main.c
		$(CC) $(CFLAGS) vmem_nru.h vmem_nru.c  main.c -o main

clean:
		rm -f main