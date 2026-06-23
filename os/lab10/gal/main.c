#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "buffer_sync.h"

// Global shared bounded buffer
CircularBuffer shared_cb;

// Global simulation configuration
int total_tasks_to_process = 0;

// Thread routines
void* producer_routine(void *arg) {
    int thread_id = *(int *)arg; // Will be 0
    
    for (int i = 1; i <= total_tasks_to_process; i++) {
        enqueue_task(&shared_cb, i, thread_id);
    }
    return NULL;
}

void* consumer_routine(void *arg) {
    int thread_id = *(int *)arg; // Will be 1
    int expected_task = 1;
    int integrity_failures = 0;

    for (int i = 0; i < total_tasks_to_process; i++) {
        int task_id = dequeue_task(&shared_cb, thread_id);
        
        // Strict Integrity Check: Data validation
        if (task_id != expected_task) {
            fprintf(stderr, "[CRITICAL ERROR] Integrity Breach! Expected Task: %d, Got: %d\n", 
                    expected_task, task_id);
            integrity_failures++;
        }
        expected_task++;
    }

    // Return the number of data corruptions encountered
    int *result = malloc(sizeof(int));
    *result = integrity_failures;
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <total_tasks_stress_count>\n", argv[0]);
        return 1;
    }

    total_tasks_to_process = atoi(argv[1]);
    if (total_tasks_to_process <= 0) {
        fprintf(stderr, "Error: Total tasks count must be a positive integer.\n");
        return 1;
    }

    // Initialize circular buffer and its structural elements
    shared_cb.head = 0;
    shared_cb.tail = 0;
    shared_cb.count = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        shared_cb.buffer[i] = 0;
    }

    // Initialize software-defined Peterson locks
    peterson_init(&shared_cb.head_lock);
    peterson_init(&shared_cb.tail_lock);

    pthread_t producer_thread, consumer_thread;
    int producer_id = 0; // Maps to flag[0] in head_lock
    int consumer_id = 1; // Maps to flag[1] in tail_lock

    printf("==================================================\n");
    printf("RUNNING BOUNDED BUFFER STRESS TEST WITH %d TASKS\n", total_tasks_to_process);
    printf("==================================================\n");

    // Spawn concurrent threads
    if (pthread_create(&producer_thread, NULL, producer_routine, &producer_id) != 0) {
        perror("Failed to create producer thread");
        return 1;
    }
    if (pthread_create(&consumer_thread, NULL, consumer_routine, &consumer_id) != 0) {
        perror("Failed to create consumer thread");
        return 1;
    }

    // Await execution block completion
    pthread_join(producer_thread, NULL);
    
    int *corruption_report = NULL;
    pthread_join(consumer_thread, (void **)&corruption_report);

    printf("\n==================================================\n");
    printf("STRESS TEST ANALYSIS\n");
    printf("==================================================\n");
    printf("Final Buffer Status: head=%d, tail=%d, residual_count=%d\n", 
           shared_cb.head, shared_cb.tail, shared_cb.count);
    
    if (corruption_report != NULL) {
        int failures = *corruption_report;
        free(corruption_report);
        
        if (failures == 0 && shared_cb.count == 0) {
            printf("STATUS: PASS (Peterson Locks & Memory Barriers worked flawlessly!)\n");
            printf("==================================================\n");
            return 0;
        }
    }

    printf("STATUS: FAIL (Synchronization Failures / Memory Reordering Corruptions Detected!)\n");
    printf("==================================================\n");
    return 1;
}