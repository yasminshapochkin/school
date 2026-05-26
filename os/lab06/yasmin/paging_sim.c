#include "paging_sim.h"



// logic addr = virtual addr 
// page num = there need to be put
// offset where in page

void get_page_and_offset(uint32_t logical_addr, uint32_t *page_num, uint32_t *offset){

    // see if the pointers are null
    if(!page_num || !offset){
        return;
    }
    *offset = logical_addr%PAGE_SIZE;
    *page_num = logical_addr/PAGE_SIZE;

}

// returns physical adrr
uint32_t calculate_physical_address(uint32_t frame_num, uint32_t offset){
    return((frame_num * PAGE_SIZE) + offset);
    
}

// check valid bit 
int translate_and_load(uint32_t logical_addr, PageTableEntry *page_table, int *next_free_frame){

    if(!page_table || !next_free_frame){
        return -1;
    }

    uint32_t page_num;
    uint32_t offset;

    // getting the addr
    get_page_and_offset(logical_addr, &page_num, &offset);

    // if bit is valid then rreturn the physical addrs
    if( page_table[page_num].valid == 1 ){
        return calculate_physical_address(page_num , offset);

    }
    ///else (bit isnt valid) -> page fault
    else if( page_table[page_num].valid == 0){
        // add to the next frame
        if(next_free_frame < NUM_FRAMES){
            // updating the array 
            page_table[page_num].frame_number = next_free_frame;
            page_table[page_num].valid = 1;
            // moving the pointer
            (*next_free_frame)++;
            // return the physical adrr
            return calculate_physical_address(next_free_frame , offset);

        }
        else{ // if no more free space
            return -1;
        }
        
    }


}



