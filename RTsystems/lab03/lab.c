/*EXPERIMENT 3*/
/* includes */
#include "vxWorks.h"
#include "taskLib.h"
#include "semLib.h"
#include "stdio.h"

#define ITER 10
#define STACK_SIZE 2000
/* function prototypes */
void taskOne(void);
void taskTwo(void);
/* globals */

SEM_ID sem;
int global = 0;
void binary(void){
    int taskIdOne, taskIdTwo;
    /* create semaphore with semaphore available and queue tasks on FIFO basis */
    sem = semCCreate(SEM_Q_FIFO, 1);
    /* Note 1: lock the semaphore for scheduling purposes */
    semTake(sem,WAIT_FOREVER);
    /* spawn the two tasks */
    taskIdOne = taskSpawn("t1",101,0x100,STACK_SIZE,(FUNCPTR)taskOne,0,0,0,0,0,0,0,0,0,0);
    taskIdTwo = taskSpawn("t2",101,0x100,STACK_SIZE,(FUNCPTR)taskTwo,0,0,0,0,0,0,0,0,0,0);
}

void taskOne(void){
    int i;
    for (i=0; i < ITER; i++){
        semTake(sem,WAIT_FOREVER); /* wait indefinitely for semaphore */
        printf("I am taskOne and global = %d......................\n", ++global);
        semGive(sem); /* give up semaphore */
    }
}

void taskTwo(void){
    int i;
    semGive(semBinary); /* Note 2: give up semaphore(a scheduling fix) */
    for (i=0; i < ITER; i++){
        semTake(sem,WAIT_FOREVER); /* wait indefinitely for semaphore */
        printf("I am taskTwo and global = %d----------------------\n", --global);
        semGive(sem); /* give up semaphore */
    }
}


------------------------------------------------------------

#EXPERIMENT 4

