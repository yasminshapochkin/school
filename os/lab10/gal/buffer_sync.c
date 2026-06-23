#include "buffer_sync.h"

void peterson_init(PetersonLock *lock)
{
    lock->flag[0]=0;
    lock->flag[1]=0;
    int turn = -1;
}

void peterson_lock(PetersonLock *lock, int thread_id)
{
    int other = 1 - thread_id;
    lock->flag[thread_id]=1;
    lock->turn =other;
    while(flag[other] && turn== other){
        _sync_synchronize();
    }

}

void peterson_unlock(PetersonLock *lock, int thread_id)
{
    lock->flag[thread_id]=0;
}

void enqueue_task(CircularBuffer *cb, int task_id, int thread_id)
{
    while (cb->count == BUFFER_SIZE);

    peterson_lock(&cb->head_lock, thread_id);
    _sync_synchronize();
    cb->buffer[cb->head] = task_id;
    cb->head++;
    cb->head %= BUFFER_SIZE;
    cb->count++;
    peterson_unlock(&cb->head_lock, thread_id);
}

int dequeue_task(CircularBuffer *cb, int thread_id)
{
    while (cb->count == 0);

    peterson_lock(&cb->tail_lock, thread_id);
    int val = cb->buffer[cb->tail];
    cb->tail++;
    cb->tail %= BUFFER_SIZE;
    cb->count--;
    peterson_unlock(&cb->tail_lock, thread_id);
    return val;
}