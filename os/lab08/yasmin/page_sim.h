

#ifndef PAGE_SIM_H
#define PAGE_SIM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



typedef struct {

    int *inserted_order; 
    int head; 
    int tail;
    int size;
    
}FIFO;


typedef struct {

    int page_num; 
    int frame_number; 
    
    struct node *next;
    struct node *prev;

}LRU;


struct node *head;
struct node *tail;





// runs sim 
int run_fifo(int *requests,int num_requests, int frame_count );



int run_lru(int *requests,int num_requests, int frame_count );



#endif

