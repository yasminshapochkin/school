CC = gcc
CFLAGS = -Wall -g

all: main_compare

main_compare: main_compare.c scheduler_lib.c scheduler_lib.h
	$(CC) $(CFLAGS) main_compare.c scheduler_lib.c -o main_compare

clean:
		rm -f main_compare
