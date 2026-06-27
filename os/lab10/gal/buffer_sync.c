#include "buffer_sync.h"

void peterson_init(PetersonLock *lock)
{
    lock->flag[0] = 0;
    lock->flag[1] = 0;
    lock->turn = -1;
    __sync_synchronize();
}

void peterson_lock(PetersonLock *lock, int thread_id)
{
    int other = 1 - thread_id;
    lock->flag[thread_id] = 1;
    __sync_synchronize();
    lock->turn = other;
    __sync_synchronize();
    while (lock->flag[other] && lock->turn == other)
    {
        __sync_synchronize();
    }
    __sync_synchronize();
}

void peterson_unlock(PetersonLock *lock, int thread_id)
{
    __sync_synchronize();
    lock->flag[thread_id] = 0;
    __sync_synchronize();
}

void enqueue_task(CircularBuffer *cb, int task_id, int thread_id)
{
    while (1)
    {
        while (cb->count == BUFFER_SIZE)
            __sync_synchronize();

        peterson_lock(&cb->head_lock, thread_id);
        peterson_lock(&cb->tail_lock, thread_id);

        if (cb->count < BUFFER_SIZE)
        {
            cb->buffer[cb->head] = task_id;
            cb->head++;
            cb->head %= BUFFER_SIZE;
            cb->count++;
            peterson_unlock(&cb->head_lock, thread_id);
            peterson_unlock(&cb->tail_lock, thread_id);
            return;
        }
        peterson_unlock(&cb->head_lock, thread_id);
        peterson_unlock(&cb->tail_lock, thread_id);
    }
}

int dequeue_task(CircularBuffer *cb, int thread_id)
{
    while (1)
    {
        int val;
        while (cb->count == 0)
            __sync_synchronize();

        peterson_lock(&cb->head_lock, thread_id);
        peterson_lock(&cb->tail_lock, thread_id);

        if (cb->count > 0)
        {
            val = cb->buffer[cb->tail];
            cb->tail++;
            cb->tail %= BUFFER_SIZE;
            cb->count--;
            peterson_unlock(&cb->head_lock, thread_id);
            peterson_unlock(&cb->tail_lock, thread_id);
            return val;
        }
        peterson_unlock(&cb->head_lock, thread_id);
        peterson_unlock(&cb->tail_lock, thread_id);
    }
}