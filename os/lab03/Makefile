CC = gcc
CFLAGS = -Wall -g

all: task1_fork task2_exec task3_chain task4_calc task5_race

task1_fork: task1_fork.c
		$(CC) $(CFLAGS) task1_fork.c -o task1_fork

task2_exec: task2_exec.c
			$(CC) $(CFLAGS) task2_exec.c -o task2_exec

task3_chain: task3_chain.c
		$(CC) $(CFLAGS) task3_chain.c -o task3_chain

task4_calc: task4_calc.c
			$(CC) $(CFLAGS) task4_calc.c -o task4_calc

task5_race: task5_race.c
			$(CC) $(CFLAGS) task5_race.c -o task5_race


clean:
		rm -f task1_fork task2_exec task3_chain task4_calc task5_race