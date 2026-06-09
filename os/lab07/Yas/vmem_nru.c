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
        page_table[i].refrenced = 0;
        page_table[i].modified = 0;
    
    }

}

void resset_R_bit(){
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i].refrenced = 0;
        
    }
}


int access_memory(uint32_t addr , char op){
    
    // for the hit / fault
    int Status = 0;
    // get virtual memory 
    int v_page = addr / PAGE_SIZE ;
    int v_offset = addr % PAGE_SIZE;
    int frame = -1;

    // if valid = 1 
    if (page_table[v_page].valid == 1){
        frame = page_table[v_page].frame_number;
        page_table[v_page].refrenced = 1;
        // if op == w then modified 
        //if ( op == 'W' ){    page_table[v_page].modified = 1; }
        
    }
     

    // if valid = 0 not in one of the frames call func
    else {
        TOTAL_PAGE_FAULTS++;
        Status = 1;
        frame = find_free_frame();

        if (frame == -1) {
            printf("No frame found\n");
            exit(1);
        }
        // if the frame has content in it 
        free_frame(frame);

        insert_frame(frame , v_page );
    }

    if ( op == 'W' ){ 
        frames[frame]->modified = 1;
    } 

    int nru_class = (page_table[v_page].modified) + (page_table[v_page].refrenced*2);
    // for printing hit or miss
   
    int p_addr = ( frame * PAGE_SIZE) + v_offset;
    printf("Addr:%d | Page: %d | Op: %c | Frame: %d | Status: ", p_addr , v_page,  op ,frame ); 
    if(Status == 0 ){  printf("HIT");}
    else{printf("FAULT");} 
    printf(" | NRU_Class %d \n",nru_class);   
    

    return p_addr;

}


int find_free_frame(){

    int R = 0;
    int M = 0;

    // int index = 0;
    int frame = -1;
    for (int i = 0 ; i<NUM_FRAMES ; i++){
        if(frames[i] == NULL){
            return i;
        }
    }

    for (int i = 0 ; i < NUM_FRAMES ; i++){
        //printf("i=%d frame=%p\n", i, frames[i]);
        if( (frames[i]->modified == M && frames[i]->refrenced == R) ){
            if (frame == -1){
                frame = i;
            }
            else if( frame != -1 && ( frame > frames[i] - page_table) ){
                frame = i;
            }
            
        }
        // if finished loop 
        if(i ==  NUM_FRAMES -1){
            // found a frame
            if(frame != -1 ){
                break;
            }
            i = -1;
            // see if finished all groups
            if(R == 1 && M==1){
                break;
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
    if (frames[index] == NULL) {
        return;
    }
    int page_num = frames[index] - page_table ;
    //printf("%d \n" , frames[index]->modified);
    if(frames[index]->modified == 1){
        //printf("modified found\n");
        TOTAL_DISK_WRITES++;
        printf("Evicting dirty page %d \n" , page_num);
    }
    frames[index]->valid = 0;
    frames[index]->modified = 0;
    frames[index]->frame_number = -1;
    frames[index]->refrenced = 0;

    frames[index] = NULL;
}




void insert_frame(int frame_index, int page_index){
    frames[frame_index] = &page_table[page_index];
    frames[frame_index]->valid = 1;
    frames[frame_index]->frame_number = frame_index;
    frames[frame_index]->refrenced = 1;

}

