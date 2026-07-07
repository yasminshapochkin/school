#include "pipeline.h"
#include <stdio.h>
#include <stdlib.h>
extern DataPipeline pipeline;
extern int total_elements_to_process;

void init_buffer(BoundedBuffer *buf)
{
    buf->head = 0;
    buf->tail = 0;
    sem_init(&buf->empty, 0, BUFF_SIZE);
    sem_init(&buf->full, 0, 0);
    sem_init(&buf->mutex, 0, 1);
}

void write_buffer(BoundedBuffer *buf, int val)
{
    sem_wait(&buf->empty);
    sem_wait(&buf->mutex);

    buf->buffer[buf->tail] = val;
    buf->tail = (buf->tail + 1) % BUFF_SIZE;

    sem_post(&buf->mutex);
    sem_post(&buf->full);
}

int read_buffer(BoundedBuffer *buf)
{
    sem_wait(&buf->full);
    sem_wait(&buf->mutex);
    int var = buf->buffer[buf->head];
    buf->head = (buf->head + 1) % BUFF_SIZE;
    sem_post(&buf->mutex);
    sem_post(&buf->empty);
    return var;
}

void *thread_A_generator(void *arg)
{
    (void) arg; 
    for (int i = 1; i <= total_elements_to_process; i++)
    {
        write_buffer(&pipeline.buf1, i);
    }
    write_buffer(&pipeline.buf1, -1);
    return NULL;
}

void *thread_B_transformer(void *arg)
{
    (void) arg; 
    int res = 0;
    while ((res=read_buffer(&pipeline.buf1) )!= -1)
    {
        write_buffer(&pipeline.buf2, res * 2);
    }
    write_buffer(&pipeline.buf2, -1);
    return NULL;
}

void *thread_C_verifier(void *arg)
{
    (void) arg;   
    int *failures = malloc(sizeof(int));
    if (!failures)
    {
        fprintf(stderr, "Error: cannot allocate memory for failures counter.\n");
        exit(-1);
    }
    *failures = 0;
    int expected = 2;
    int res = 0;
    while ((res = read_buffer(&pipeline.buf2)) != -1)
    {
        if (res != expected)
            __sync_fetch_and_add(failures,1);
        expected += 2;
    }
    return failures;
}