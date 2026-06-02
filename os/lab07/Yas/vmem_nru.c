#include "vmem_nru.h"


PageTableEntry page_table[NUM_PAGES];
PageTableEntry* frames[NUM_FRAMES];

int TOTAL_PAGE_FAULTS = 0;
int TOTAL_DISK_WRITES = 0;


int get_page_faults(){
    return TOTAL_PAGE_FAULTS;
}

int get_disk_writes(){
    return TOTAL_DISK_WRITES;
}

void init_frames(){
    // inisialize the frames 
    for (int i = 0 ; i <NUM_FRAMES;i++ ){
        frames[i] = NULL;
    }

}

void init_page_table(){
    //inisialize table
    for (int i = 0; i < NUM_PAGES; i++) {

        page_table[i].frame_number = -1;
        page_table[i].valid = 0;
        page_table[i].referenced = 0;
        page_table[i].modified = 0;
    
    }

}

void resset_R_bit(){
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i]->referenced = 0;
    }
}


int access_memory(uint32_t addr , char op){
    
    
    // get virtual memory 
    int v_page = addr / PAGE_SIZE ;
    int v_offset = addr % PAGE_SIZE;

    // if valid = 1 
    if (page_table[v_page].valid == 1){
        
        page_table[v_page].referenced = 1;
        // if op == w the modified 
        if ( op == 'W' ){ 
            page_table[v_page].modified = 1;
        }
        
    }
    // for the hit / fault
    int Status = 0; 

    // if valid = 0 not in one of the frames call func
    else {
        TOTAL_PAGE_FAULTS++;
        Status = 1;
        int frame = find_free_frame();
        // if the frame has content in it 
        if(frames[frame] != NULL){

            free_frame(frame);

        }
        insert_frame(frame , v_page );

    }
    int nru_class = (page_table[v_page].modified*1) + (page_table[v_page].referenced*2);
     // for printing hit or miss
    string H_F = ["HIT","FAULT"];
    int p_addr = (frame*PAGE_SIZE) + v_offset;
    printf("Addr:%d | Page: %d | Op: %c | Frame: %d | Status: %s | NRU_Class %d \n",
            p_addr,      v_page,      op,   ,    frame,  H_F[Status]  ,nru_class); 
}


int find_free_frame(){
    int R = 0;
    int M = 0;
    int index = 0;
    int frame = -1;

    for (int i = 0 ; i<NUM_FRAMES ; i++){

        if(frames[i] == NULL || frames[i]->modified == M && frames[i]->referenced == R ){
            frame = i;
            breake;
        }
        // if finished loop 
        if(i ==  NUM_FRAMES -1){
            i = -1;
            // see if finished all groups
            if(R == 1 && M==1){
                breake;
            }
            // update bits
            if(M==0){
                M++;
            }
            else if(R==0){
                R++;
                M--;
            }
        }
    }
    return frame;
}



void free_frame(int index){
    int page_num = frame[index] - page_table ;
    if(frame[index]->modified == 1){
        TOTAL_DISK_WRITES++;
        printf("Evicting dirty page %d \n" , page_num);
    }
    frame[index]->valid = 0;
    frame[index]->modified = 0;
    frame[index]->frame_number = -1;
    frame[index]->modified = 0;
}



void insert_frame(int frame_index, int page_index){
    frame[frame_index] = page_table[page_index];
    frame[frame_index]->valid = 1;
    frame[frame_index]->frame_number = frame_index;
    frame[frame_index]->modified = 0;
    frame[frame_index]->modified = 0;
}

