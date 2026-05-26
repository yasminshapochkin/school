#include "paging_sim.h"



// logic addr = virtual addr 
// page num = there need to be put
// offset where in page

void get_page_and_offset(uint32_t logical_addr, uint32_t *page_num, uint32_t *offset){

    *offset = logical_addr%PAGE_SIZE;
    *page_num = logical_addr/PAGE_SIZE;

}

uint32_t calculate_physical_address(uint32_t frame_num, uint32_t offset){



}


