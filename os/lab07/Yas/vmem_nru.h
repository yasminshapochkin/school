#ifndef VMEM_NRU_H
#define VMEM_NRU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define PAGE_SIZE 4096
#define NUM_PAGES 16
#define NUM_FRAMES 4
#define PHYS_MEM_SIZE (NUM_FRAMES * PAGE_SIZE)


typedef struct {
    int frame_number ; 
    int valid;
    int refrenced;
    int modified;

}PageTableEntry;



int get_page_faults();
int get_disk_writes();
void init_frames();
void init_page_table();
void resset_R_bit();
int access_memory(uint32_t addr , char op);
int find_free_frame();
void free_frame(int index);
void insert_frame(int frame_index, int page_index);

#endif