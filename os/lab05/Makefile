CC = gcc
CFLAGS = -Wall -g

all: main_memory

main_memory: main_memory.c memory_manager.c memory_manager.h
		$(CC) $(CFLAGS) main_memory.c memory_manager.c -o main_memory




clean:
		rm -f main_memory
