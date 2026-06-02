CC = gcc
CFLAGS = -Wall -g

all: main

main: main.c vmem_nru.c 
	$(CC) $(CFLAGS) main.c vmem_nru.c -o main

clean:
		rm -f main
