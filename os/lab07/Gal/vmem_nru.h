#ifndef VMEM_NRU_H
#define VMEM_NRU_H

#define PAGE_SIZE 4096
#define NUM_PAGES 16
#define NUM_FRAMES 4
#include <stdio.h>
#include <stdint.h>

int faults=0;
int modified=0;

typedef struct PageTableEntry{
    int frame_number;
    int valid;
    int referenced;
    int modified;
} PageTableEntry;

void init_frames();
void init_paga_table();

int access_memory(uint32_t adrr, char op);
void NRU(int pageNum);

void reset_R_bit()
void insertFrame(int frameinx, int pageNum);
int allocateFreeFrame();
#endif