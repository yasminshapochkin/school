#ifndef PAGE_SIM_H
#define PAGE_SIM_H

#define MAX_VPAGE 100

#include <stdbool.h>
typedef struct FIFOStruct
{
    int *frames;
    int first;
    int last;
    int size;
} FIFOStruct;

typedef struct node_LRU
{
    int page_num;
    int frame_number;
    struct node_LRU *next;
    struct node_LRU *prev;
} node_LRU;

node_LRU *head;
node_LRU *tail;

bool in_frames(int *frames, int page, int frame_count);

int run_fifo(int *request, int num_requests, int frame_count);

int run_lru(int *request, int num_requests, int frame_count);

#endif