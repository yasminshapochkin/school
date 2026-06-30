#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pipeline.h"

// Global shared pipeline object
DataPipeline pipeline;

// Global workload tracking variable
int total_elements_to_process = 0;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <total_elements_stress_count>\n", argv[0]);
        return 1;
    }

    total_elements_to_process = atoi(argv[1]);
    if (total_elements_to_process <= 0) {
        fprintf(stderr, "Error: Element count must be a positive integer.\n");
        return 1;
    }

    // Initialize both bounded buffers inside the multi-stage pipeline
    init_buffer(&pipeline.buf1);
    init_buffer(&pipeline.buf2);

    pthread_t threadA, threadB, threadC;

    printf("==================================================\n");
    printf("STARTING MULTI-STAGE DATA PIPELINE STRESS TEST\n");
    printf("Processing Workload: %d Elements through 2 Buffers\n", total_elements_to_process);
    printf("==================================================\n");

    // Launch all three pipeline stages concurrently
    if (pthread_create(&threadA, NULL, thread_A_generator, NULL) != 0) {
        perror("Failed to create thread A");
        return 1;
    }
    if (pthread_create(&threadB, NULL, thread_B_transformer, NULL) != 0) {
        perror("Failed to create thread B");
        return 1;
    }
    if (pthread_create(&threadC, NULL, thread_C_verifier, NULL) != 0) {
        perror("Failed to create thread C");
        return 1;
    }

    // Await completion of all cascade stages
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    
    int *verification_failures = NULL;
    pthread_join(threadC, (void **)&verification_failures);

    printf("\n==================================================\n");
    printf("PIPELINE EXECUTION REPORT\n");
    printf("==================================================\n");
    
    if (verification_failures != NULL) {
        int failures = *verification_failures;
        free(verification_failures); // Clean up the heap-allocated diagnostic log
        
        if (failures == 0) {
            printf("STATUS: PASS (All elements processed, transformed, and verified!)\n");
            printf("==================================================\n");
            return 0;
        }
    }

    printf("STATUS: FAIL (Pipeline Corruption / Missing Elements Detected!)\n");
    printf("==================================================\n");
    return 1;
}