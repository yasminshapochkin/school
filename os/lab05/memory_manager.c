#include "memory_manager.h"
#include <stdlib.h>
#include <stdio.h>
Segment *init_memory(int total_size)
{
    Segment *memory;
    memory->is_process = 1;
    memory->process_id = -1;
    memory->start_address = 0;
    memory->size = 1024;
    memory->next = NULL;
    return memory;
}

void print_memory(Segment *head)
{
    while (head)
    {
        printf("[%s, Addr: %d, Size: %d] -> ", get_id(head->process_id), head->start_address, head->size);
        head = head->next;
    }
    printf("NULL\n");
}

char* get_id(int i)
{
    if (i == 1)
        return 'H';
    else
        return 'P'+i;
}

void print_stats(Segment *head)
{
    int totalMem = 0;
    int usedMem = 0;
    int freeMem = 0;
    int numProc = 0;
    int numHoles = 0;
    while (head)
    {
        totalMem += head->size;
        if (head->is_process == 1)
        {
            freeMem += head->size;
            numHoles++;
        }
        else
        {
            usedMem += head->size;
            numProc++;
        }
        head = head->next;
    }
    float precFM = (freeMem / totalMem) * 100;
    float precUM = (usedMem / totalMem) * 100;
    printf("--- Memory Statistics ---\n");
    printf("Total Memory: %d units\n", totalMem);
    printf("Used Memory: %d units (%f%)\n", usedMem, precUM);
    printf("Free Memory: %d units (%f%)\n", freeMem, precFM);
    printf("Number of Segments: %d (%d processes, %d holes)\n", numProc + numHoles, numProc, numHoles);
    printf("-------------------------");
}

Segment *allocate_first_fit(Segment *head, int process_id, int size)
{
    Segment* ret= head;
    while (head)
    {
        if (head->is_process == 1 && head->size >= size)
        {
            break;
        }
        head = head->next;
    }
    if (!head)
    {
        fprinf(stderr, "Out of Memory.\n");
            exit(1);
    }
    if (head->size > size)
    {
        Segment* temp=head->next;
        Segment* newHole;
        int totSize= head->size;
        head->is_process=0;
        head->process_id= process_id;
        head->size= size;

        newHole->is_process=1;
        newHole->process_id=-1;
        newHole->start_address = head->start_address + size;
        newHole->size = totSize - size;
        newHole->next = temp;
    }else{
        head->is_process=0;
        head->process_id= process_id;
    }
    return ret;
}

Segment* allocate_best_fit(Segment *head, int process_id, int size){
    Segment* ret= head;
    Segment* bstFit=head;
    while(head){
        if(head->is_process == 1 && head->size < bstFit->size && size <= head->size){
            bstFit=head;
        }
        head= head->next;
    }
    if (!bstFit|| bstFit->is_process == 0);
    {
        fprinf(stderr, "Out of Memory.\n");
            exit(1);
    }
    if (bstFit->size > size)
    {
        Segment* temp=bstFit->next;
        Segment* newHole;
        int totSize= bstFit->size;
        bstFit->is_process=0;
        bstFit->process_id= process_id;
        bstFit->size= size;

        newHole->is_process = 1;
        newHole->process_id = -1;
        newHole->start_address = bstFit->start_address + size;
        newHole->size = totSize - size;
        newHole->next = temp;
    }else{
        bstFit->is_process = 0;
        bstFit->process_id = process_id;
    }
    return ret;
}

