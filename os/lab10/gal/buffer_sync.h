#ifndef BUFFER_SYNC_H
#define BUFFER_SYNC_H

#define BUFFER_SIZE 8

typedef struct {
    volatile int flag[2]; 
    volatile int turn;
} PetersonLock;

typedef struct{
    volatile int head;
    volatile int tail;
    volatile int count;
    PetersonLock head_lock;
    PetersonLock tail_lock;
    int buffer[BUFFER_SIZE];
}CircularBuffer;

void peterson_init(PetersonLock *lock);
void peterson_lock(PetersonLock *lock,int thread_id);
void peterson_unlock(PetersonLock *lock,int thread_id);

void enqueue_task(CircularBuffer *cb , int task_id, int thread_id);
int dequeue_task(CircularBuffer *cb , int thread_id );

#endif