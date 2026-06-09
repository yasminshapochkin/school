

// runs sim both ask for frames num while runin 





// circle array  we make full saize array and move with a pointer
int run_fifo(int *requests ,int num_requests, int frame_count ){
    int FRAMES_NUM ;
    //get number of frames
    scanf("%d", &FRAMES_NUM);
    // inisialize data structur
    FIFO fifo;
    fifo.size = FRAMES_NUM;
    fifo.head = 0;
    fifo.tail = 0;
    // allocate memory
    fifo.inserted_order = malloc(sizeof(int) * fifo.size);

    for (int i = 0; i < fifo.size; i++) {
        fifo.inserted_order[i] = -1;
    }

    int PAGE_FAULTS_COUNT = 0 ;
    for(int i = 0 ; i < num_requests ; i++){
        // add, if not, get a frame out 
        if(fifo.inserted_order[tail] == -1 ){
            
        }

    }

    
    // free aloocation
    free(fifo.inserted_order);
}



int run_lru(int *requests,int num_requests, int frame_count ){
    

}


