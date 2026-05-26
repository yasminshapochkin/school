CC = gcc
CFLAGS = -Wall -g

all: main_paging

main_paging: paging_sim.h paging_sim.c  main_paging.c
		$(CC) $(CFLAGS) paging_sim.c main_paging.c -o main_paging




clean:
		rm -f main_paging
