#ifndef PIPELINE_H
#define PIPELINE_H
#include <semaphore.h>

#define BUFF_SIZE 5

typedef struct
{
    volatile int buffer[BUFF_SIZE];
    volatile int head;
    volatile int tail;
    sem_t empty;
    sem_t full;
    sem_t mutex;
} BoundedBuffer;

typedef struct
{

    BoundedBuffer buf1;
    BoundedBuffer buf2;

} DataPipeline;

void init_buffer(BoundedBuffer *buf);
void write_buffer(BoundedBuffer *buf, int val);
int read_buffer(BoundedBuffer *buf);

void *thread_A_generator(void *arg);
void *thread_B_transformer(void *arg);
void *thread_C_verifier(void *arg);

#endif