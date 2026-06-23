
#ifndef BUFFER_SYNC_H
#define BUFFER_SYNC_H

typedef struct {
    int flag[2];  
    int turn;
} PetersonLock;


typedef struct {
    int* flag ;  
    int head;
    int tail;
    int count;


}CircularBuffer;

void peterson_init(PetersonLock *lock);
void peterson_lock(PetersonLock *lock);
void peterson_unlock(PetersonLock *lock);

void enqueue_task(CircularBuffer *cb , int task_id, int thread_id);
int dequeue_task(CircularBuffer *cb , int task_id );

#endif