CC = gcc
CFLAGS = -Wall -g

all: main_paging

main_paging: paging_sim.h paging_sim.c  main_paging.c
		$(CC) $(CFLAGS) paging_sim.c main_paging.c -o main_paging

my_chmod: my_chmod.c
			$(CC) $(CFLAGS) my_chmod.c -o my_chmod


clean:
		rm -f main_paging my_chmod
