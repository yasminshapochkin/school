CC = gcc
CFLAGS = -Wall -g

all: task1_fork task2_exec task3_chain task4_calc task5_race

main_compare: main_compare.c schedular_lib.h schedular_lib.c
		$(CC) $(CFLAGS) main_compare.c schedular_lib.h schedular_lib.c -o main_compare


clean:
		rm -f main_compare
