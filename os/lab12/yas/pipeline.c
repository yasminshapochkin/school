

#include "pipeline.h"

extern SharedResource sr;   

void init_resource(SharedResource* sr){
    sr->shared_database = 0;
    sr->read_count = 0;
    sr->write_count = 0;
    sem_init(&sr->mutex_r, 0, 1);
    sem_init(&sr->mutex_w, 0, 1);
    sem_init(&sr->queue_block, 0, 1);
    sem_init(&sr->resource_access, 0, 1);
}


void* reader_worker(void* arg){
    int id = *((int*)arg);
    sem_wait(&sr.queue_block);

    sem_wait(&sr.mutex_r);
    
    sr.read_count++;
    
    sem_post(&sr.mutex_r);

    printf("d%\n", sr.shared_database);



    sem_wait(&sr.mutex_r);
    read_count--;
    if(sr.read_count == 0){
        sem_post(&sr.resource_access);
    }
    sem_post(&sr.mutex_r);
    return NULL;

}

void* writer_worker(void* arg){
    int id = *((int*)arg);
    sem_wait(&sr.mutex_w);
    sr.write_count++;
    if(sr.write_count == 1){
        sem_wait(&sr.queue_block);
    }
    sem_post(&sr.sr.mutex_w);

    sem_wait(&sr.resource_access);
    sr.shared_database++;
    sem_post(&sr.resource_access);

    sem_wait(&sr.mutex_w);
    sr.write_count--;

    if(sr.write_count == 0){
        sem_post(&sr.queue_block);
    }

    sem_post(&sr.mutex_w);





}










