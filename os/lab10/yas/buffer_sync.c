#include "buffer_sync.h"

// decidees whos next
void peterson_init(PetersonLock *lock){
    lock->flag[0] = 0;
    lock->flag[1] = 0;
    lock->turn = 0;

}

//  while (flag[other] && turn == other);

void peterson_lock(PetersonLock *lock , int thread_id){
    int other = 1 - thread_id;
    lock->flag[thread_id] = 1;
    lock->turn =  other;
    while (lock->flag[other] && lock->turn == other){
        __sync_synchronize();
    }
}


void peterson_unlock(PetersonLock *lock  , int thread_id){
    lock->flag[thread_id] = 0;
}

void enqueue_task(CircularBuffer *cb , int task_id, int thread_id){
    
    // if queue isnt full 
    
   // if (cb->count == 8 ){ while (cb->head_lock->flag[other] && lock->turn == other); }
    while (cb->count == BUFFER_SIZE) {
        /* code */
        __sync_synchronize();
    }
    // lock the right lock 
    peterson_lock( cb->head_lock , thread_id );
    __sync_synchronize();

    // add task id to the תא ה head in the array
    cb->buffer[cb->head] = task_id;
     // move head by one
    cb->head = cb->head == 8 ? 0 : cb->head++  ;   
    
     // update count
    cb->count++; 
     //releace lock 
    __sync_synchronize();
    peterson_unlock( cb->head_lock , thread_id );
    
    

}

int dequeue_task(CircularBuffer *cb , int thread_id ){
    // if queue is empty 
    while (cb->count == 0 ){
         // wait
        __sync_synchronize();
    }
    
        // lock tail
        peterson_lock( cb->tail_lock , thread_id );
        __sync_synchronize();

        // get value from arr
        int t = cb->buffer[cb->tail];
        // move tail by one
        cb->tail = cb->tail == 8 ? 0 : cb->tail++  ;
        cb->count--;
        //releace lock
        __sync_synchronize();
        peterson_unlock( cb->tail_lock , thread_id );
    
    return t;

}