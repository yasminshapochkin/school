
#ifndef BUFFER_SYNC_H
#define BUFFER_SYNC_H

#define BUFFER_SIZE 8


typedef struct {
    volatile int flag[2];  
    volatile int turn;
} PetersonLock;


typedef struct {
    int* buffer ;  
    volatile int head;
    volatile int tail;
    volatile int count;
    PetersonLock* head_lock;
    PetersonLock* tail_lock;


}CircularBuffer;

// must use volatile for the sync 

void peterson_init(PetersonLock *lock);
void peterson_lock(PetersonLock *lock);
void peterson_unlock(PetersonLock *lock);

void enqueue_task(CircularBuffer *cb , int task_id, int thread_id);
int dequeue_task(CircularBuffer *cb , int task_id );

#endif