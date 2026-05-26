#include "paging_sim.h"
#include <stdio.h>
#include <stdlib.h>
void get_page_and_offset(uint32_t logical_addr, uint32_t *page_num, uint32_t *offset)
{
    if (page_num && offset)
    {
        *page_num = logical_addr / PAGE_SIZE;
        *offset = logical_addr % PAGE_SIZE;
    }
}

uint32_t calculate_physical_address(uint32_t frame_num, uint32_t offset)
{
    return (frame_num * PAGE_SIZE)+offset;
}

int translate_and_load(uint32_t logical_addr, PageTableEntry *page_table, int *next_free_frame){
    if (!page_table || !next_free_frame){
        return -1;
    }
    uint32_t page_num;
    u_int32_t offset;
    get_page_and_offset(logical_addr,&page_num,&offset);
    
    page_table+=page_num;

    int validbit=page_table->valid;

    if(validbit== 1){
        return calculate_physical_address(page_table->frame_number,offset);
    }
    else{ // pagefault
        if(*next_free_frame >NUM_FRAMES){
            return -1;
        }
        page_table->frame_number = *next_free_frame;
        page_table->valid = 1;
        next_free_frame++;
        return calculate_physical_address(page_table->frame_number,offset);
    }

}
