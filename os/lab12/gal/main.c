#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "pipeline.h"

// Global instantiation of the shared resource configuration
SharedResource target_resource;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <num_readers> <num_writers>\n", argv[0]);
        return 1;
    }

    int num_readers = atoi(argv[1]);
    int num_writers = atoi(argv[2]);

    if (num_readers <= 0 || num_writers <= 0) {
        fprintf(stderr, "Error: Thread counts must be positive integers.\n");
        return 1;
    }

    // Initialize the shared database, state counters, and POSIX semaphores
    init_resource(&target_resource);

    pthread_t *readers = (pthread_t *)malloc(num_readers * sizeof(pthread_t));
    pthread_t *writers = (pthread_t *)malloc(num_writers * sizeof(pthread_t));
    
    int *reader_ids = (int *)malloc(num_readers * sizeof(int));
    int *writer_ids = (int *)malloc(num_writers * sizeof(int));

    if (!readers || !writers || !reader_ids || !writer_ids) {
        perror("Failed to allocate memory for thread tracking arrays");
        return 1;
    }

    printf("==================================================\n");
    printf("STARTING READERS-WRITERS SIMULATION (WRITERS-PRIORITY)\n");
    printf("Spawning: %d Readers | %d Writers\n", num_readers, num_writers);
    printf("==================================================\n\n");

    // Launch writer threads concurrently
    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer_worker, &writer_ids[i]) != 0) {
            perror("Failed to create writer thread");
            return 1;
        }
    }

    // Launch reader threads concurrently
    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader_worker, &reader_ids[i]) != 0) {
            perror("Failed to create reader thread");
            return 1;
        }
    }

    // Await termination of all reader lifecycle routines
    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }

    // Await termination of all writer lifecycle routines
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    printf("\n==================================================\n");
    printf("SIMULATION COMPLETED SUCCESSFULLY\n");
    printf("Final Shared Database Value: %d\n", target_resource.shared_database);
    printf("==================================================\n");

    // Free dynamic allocations
    free(readers);
    free(writers);
    free(reader_ids);
    free(writer_ids);

    return 0;
}