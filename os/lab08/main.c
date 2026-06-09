#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_sim.h"

#define MAX_REQUESTS 1000

/* DO NOT MODIFY THIS FILE.
   This file handles input parsing and drives the simulation for both FIFO and LRU.
   Your implementation must match the output format generated here.
*/

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <page_requests.txt> <frame_count>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int frame_count = atoi(argv[2]);

    if (frame_count <= 0) {
        fprintf(stderr, "Error: frame_count must be a positive integer.\n");
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening input file");
        return 1;
    }

    int requests[MAX_REQUESTS];
    int num_requests = 0;

    // Read the reference string from the input file
    while (fscanf(file, "%d", &requests[num_requests]) == 1) {
        num_requests++;
        if (num_requests >= MAX_REQUESTS) {
            fprintf(stderr, "Warning: Maximum request limit reached (%d).\n", MAX_REQUESTS);
            break;
        }
    }
    fclose(file);

    if (num_requests == 0) {
        fprintf(stderr, "Error: No page requests found in the file.\n");
        return 1;
    }

    // Execute and print results for FIFO Simulation
    printf("=====================================\n");
    printf("Executing FIFO Simulation (Frames: %d)\n", frame_count);
    printf("=====================================\n");
    int fifo_faults = run_fifo(requests, num_requests, frame_count);

    // Execute and print results for LRU Simulation
    printf("\n=====================================\n");
    printf("Executing LRU Simulation (Frames: %d)\n", frame_count);
    printf("=====================================\n");
    int lru_faults = run_lru(requests, num_requests, frame_count);

    // Final Comparative Statistical Report
    printf("\n=====================================\n");
    printf("FINAL SIMULATION SUMMARY (Frames: %d)\n", frame_count);
    printf("=====================================\n");
    printf("Total Page Requests: %d\n", num_requests);
    printf("FIFO Page Faults:    %d\n", fifo_faults);
    printf("LRU Page Faults:     %d\n", lru_faults);
    printf("=====================================\n");

    return 0;
}