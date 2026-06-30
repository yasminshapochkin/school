#include "pipeline.h"
extern DataPipeline pipeline;
extern int total_element_to_process;

void init_buffer(BoundedBuffer *buf)
{
    buf->head = 0;
    buf->tail = 0;
    sem_init(buf->empty, 0, BUFF_SIZE);
    sem_init(buf->full, 0, 0);
    sem_init(buf->mutex, 0, 1);
}

void write_buffer(BoundedBuffer *buf, int val)
{
    sem_wait(buf->empty);
    sem_wait(buf->mutex);

    buf->buffer[buf->tail];
    buf->tail = (buf->tail + 1) % BUFF_SIZE;

    sem_post(buf->mutex);
    sem_post(buf->full);
}

int read_buffer(BoundedBuffer *buf)
{
    sem_wait(buf->full);
    sem_wait(buf->mutex);
    int var = buf->buffer[head];
    buf->head = (buf->head - 1) % BUFF_SIZE;
    sem_post(buf->mutex);
    sem_post(buf->empty);
    return var;
}

void *thread_A_generator(void *arg)
{
    for (int i = 1; i < total_element_to_process; i++)
    {
        write_buffer(&pipeline.AtB, i);
    }
    write_buffer(&pipeline.AtB, -1);
}

void *thread_B_transformer(void *arg)
{
    int res = 0;
    while (res != -1)
    {
        res = read_buffer(&pipeline.AtB);
        write_buffer(&pipeline.BtC, res * 2);
    }
    write_buffer(pipeline.BtC, res);
}

void *thread_C_verifier(void *arg)
{
    int res = 0;
    while (res != -1)
    {
        res = read_buffer(&pipeline.BtC);
        
    }
}