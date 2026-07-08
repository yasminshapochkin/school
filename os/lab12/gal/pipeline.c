#include "pipeline.h"
#include <unistd.h>
extern SharedResource target_resource;
void init_resource(SharedResource *sr)
{
    sr->shared_database = 0;
    sr->write_count = 0;
    sr->read_count = 0;
    sem_init(&sr->mutex_r, 0, 1);
    sem_init(&sr->mutex_w, 0, 1);
    sem_init(&sr->queue_block, 0, 1);
    sem_init(&sr->resource_access, 0, 1);
}

void *reader_worker(void *arg)
{
    (void)arg;
    for (int i = 0; i < 3; i++)
    {
        sem_wait(&target_resource.queue_block);
        sem_wait(&target_resource.mutex_r);
        target_resource.read_count++;
        if (target_resource.read_count == 1)
        {
            sem_wait(&target_resource.resource_access);
        }
        sem_post(&target_resource.mutex_r);

        sem_post(&target_resource.queue_block);

        printf("%d\n", target_resource.shared_database);

        sem_wait(&target_resource.mutex_r);
        target_resource.read_count--;

        if (target_resource.read_count == 0)
        {
            sem_post(&target_resource.resource_access);
        }

        sem_post(&target_resource.mutex_r);
        usleep(1000);
    }
    return NULL;
}

void *writer_worker(void *arg)
{
    (void)arg;
    for (int i = 0; i < 3; i++)
    {
        sem_wait(&target_resource.mutex_w);
        target_resource.write_count++;
        if (target_resource.write_count == 1)
        {
            sem_wait(&target_resource.queue_block);
        }
        sem_post(&target_resource.mutex_w);
        sem_wait(&target_resource.resource_access);

        target_resource.shared_database++;

        sem_post(&target_resource.resource_access);

        sem_wait(&target_resource.mutex_w);
        target_resource.write_count--;
        if (target_resource.write_count == 0)
        {
            sem_post(&target_resource.queue_block);
        }
        sem_post(&target_resource.mutex_w);
        usleep(1000);
    }
    return NULL;
}