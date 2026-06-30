#include "pipeline.h"
extern int total_elements_to_process;
extern PipeLine pipeline;

void init_buffer(BoundedBuffer *buf){
    //initialize the buffer indices and semaphores
    buf->head = 0;
    buf->tail = 0;
    // sem_init -> inisializez the semaphores for empty, full, and mutex
    sem_init(&buf->empty, 0, BUFF_SIZE);
    sem_init(&buf->full, 0, 0);
    sem_init(&buf->mutex, 0, 1);
}
//write -> on the tail
void write_buffer(BoundedBuffer *buf, int val){

    //lock so only i can accses
    sem_wait(&buf->empty);
    sem_wait(&buf->mutex);

    //write into the buffer and move the tail index
    buf->buffer[buf->tail] = val;
    buf->tail = (buf->tail + 1) % BUFF_SIZE;
    
    //unlock so others can accses
    sem_post(&buf->mutex);
    sem_post(&buf->full);
    

}

// read on the head
int read_buffer(BoundedBuffer *buf){

    //its main job is to low the number by 
    // sem_init -> הורדה וחסימה
    
    sem_wait(&buf->full);
    sem_wait(&buf->mutex);

    // write into the 
    buf->buffer[buf->head] = val;
    buf->head = (buf->head + 1) % BUFF_SIZE;

    // sem_post -> העלאה ושחרור
    sem_post(&buf->mutex);
    sem_post(&buf->empty);

}

void *thread_A_generator(void *arg){
    for (int i = 0; i < total_elements_to_process; i++) {
        write_buffer(&pipeline.AtB, i);
    }
    write_buffer(&pipeline.AtB, -1); // signal end of data
}

void *thread_B_transformer(void *arg){
    int val;
    while(1){
        read_buffer(&pipeline.AtB, &val);
        if (val == -1) { // check for end signal
            write_buffer(&pipeline.BtC, -1); // propagate end signal
            break;
        }
        else{ // mutliply by 2 if isnt the end
            write_buffer(&pipeline.BtC, val * 2); 
        }
    }

}
void *thread_C_verifier(void *arg){

    int val;
    while(1){
        read_buffer(&pipeline.AtB, &val);
         // see if its the end
        if (val == -1) {
            break;
        }
        // check if the value is valid
        else if(){ 
            
        }


    }

    /*
    int val;
    int failures = 0;
    while(true){
        read_buffer(&pipeline.BtC, &val);
        if (val == -1) { // check for end signal
            break;
        }
        else{ // check if the value is even
            if (val % 2 != 0) {
                failures++;
            }
        }
    }
    int *result = malloc(sizeof(int));
    *result = failures;
    return result;*/
}