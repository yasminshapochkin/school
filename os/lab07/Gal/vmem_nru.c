#include "vmem_nru.h"
#include <stdlib.h>
#include <string.h>

int faults=0;
int modified=0;
PageTableEntry page_table[NUM_PAGES];
PageTableEntry *frames[NUM_FRAMES];

void init_frames()
{
    for (int i = 0; i < NUM_FRAMES; i++)
        frames[i] = NULL;
}

void init_paga_table()
{
    for (int i = 0; i < NUM_PAGES; i++)
    {
        page_table[i].frame_number = -1;
        page_table[i].valid = 0;
    }
}

int access_memory(uint32_t addr, char op)
{
    int vpage = addr / PAGE_SIZE;
    int offset = addr % PAGE_SIZE;
    int vbit = page_table[vpage].valid;

    if (vbit == 1)
    { // Page Hit
        page_table[vpage].referenced = 1;
        if (op == 'W')
            page_table[vpage].modified = 1;
    }

    else if (vbit == 0) // Page faults
    {
        faults++;
        NRU(vpage,op);
    }
    int pAddr = page_table[vpage].frame_number * PAGE_SIZE + offset;
    printf("Addr: %d | Page: %d | Op: %c | Frame: %d | Status: %s | NRU_Class: %d\n", pAddr, vpage, op, page_table[vpage].frame_number, vbit == 1 ? "HIT" : "FAULT", (page_table[vpage].modified) + (page_table[vpage].referenced * 2));
    return pAddr;
}

void NRU(int pageNum, char op)
{
    // free a frame
    int frame = allocateFreeFrame();
    if (frames[frame])
    {
        frames[frame]->frame_number = -1;
        frames[frame]->valid = 0;
        frames[frame]->referenced = 0;
        if (frames[frame]->modified == 1)
        {
            int pageToEv = frames[frame] - page_table;
            printf("Evicting dirty page %d\n", pageToEv);
            frames[frame]->modified = 0;
            modified++;
        }
    }
    insertFrame(frame, pageNum);
    if(op =='W')
        frames[frame]->modified= 1;
}

void insertFrame(int frameinx, int pageNum)
{
    frames[frameinx] = &page_table[pageNum];
    frames[frameinx]->frame_number = frameinx;
    frames[frameinx]->valid = 1;
    frames[frameinx]->referenced=1;
}

void reset_R_bit()
{
    for (int i = 0; i < NUM_FRAMES; i++)
    {
        frames[i]->referenced = 0;
    }
}

int allocateFreeFrame()
{

    int R = 0;
    int M = 0;
    for (int i = 0; i < NUM_FRAMES; i++)
    {
        if (frames[i] == NULL)
        {
            return i;
        }
        if (frames[i]->modified == M && frames[i]->referenced == R)
        {
            return i;
        }
        if (i == NUM_FRAMES - 1)
        {
            i = -1;
            if (M == 0)
                M = 1;

            else if (R == 0)
            {
                R = 1;
                M = 0;
            }
        }
    }
    exit (-1);
}