CC = gcc
CFLAGS = -Wall -g

all: main

main: page_sim.h page_sim.c  main.c
		$(CC) $(CFLAGS)  page_sim.c main.c -o main

clean:
		rm -f main