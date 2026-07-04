#include "pipeline.h"
#include <stdlib.h>
#include <stdio.h>
extern int total_elements_to_process;
extern DataPipeline pipeline;

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
    int val = buf->buffer[buf->head];
    buf->head = (buf->head + 1) % BUFF_SIZE;

    // sem_post -> העלאה ושחרור
    sem_post(&buf->mutex);
    sem_post(&buf->empty);
    return val;

}

void *thread_A_generator(void *arg){
    for (int i = 0; i < total_elements_to_process; i++) {
        write_buffer(&pipeline.buf1, i);
    }
    write_buffer(&pipeline.buf1, -1); // signal end of data
    return NULL;
}

void *thread_B_transformer(void *arg){
    int val;
    while(1){
        val = read_buffer(&pipeline.buf1);
        if (val == -1) { // check for end signal
            write_buffer(&pipeline.buf2, -1); // propagate end signal
            break;
        }
        else{ // mutliply by 2 if isnt the end
            write_buffer(&pipeline.buf2, val * 2); 
        }
    }
    return NULL;

}

//what does valid means?? 
// the series numbers is a serieas that goes up by one 
// knows that starts with 1 

// returns numebr of failiars 
void *thread_C_verifier(void *arg){
    int counter = 0;
    int fails = 0;
    int val;
    while(1){
        val = read_buffer(&pipeline.buf2);
        // see if its the end
        if (val == -1) {
            break;
        }
        // check if the value is valid ??????
        else if(counter*2 != val){ 
            __sync_fetch_and_add(&fails, 1);
        }

        counter++;
    }
    int *result = malloc(sizeof(int));
    *result = fails;
    return result;


}