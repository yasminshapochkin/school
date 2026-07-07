#ifndef PIPELINE_H
#define PIPELINE_H
#include <stdio.h>
#include <semaphore.h>

typedef struct{

    volatile int shared_database;
    
    //readers in CR
    volatile int read_count;

    //writers in CR
    volatile int write_count;

    //lock for readers counter
    sem_t mutex_r;

    //lock for writers counter
    sem_t mutex_w;

    sem_t queue_block;

    //lock for shared resource
    sem_t resource_access;

}SharedResource;

void init_resource(SharedResource* sr);

void* reader_worker(void* arg);

void* writer_worker(void* arg);

#endif