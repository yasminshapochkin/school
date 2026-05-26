CC = gcc
CFLAGS = -Wall -g

all: main_paging

main_paging: main_paging.c paging_sim.c 
	$(CC) $(CFLAGS) main_paging.c paging_sim.c -o main_paging

clean:
		rm -f main_paging
