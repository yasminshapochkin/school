#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "matrix_bench.h"

/* Helper to allocate a dynamic 2D array */
int** allocate_matrix(int N) {
    int **mat = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        mat[i] = (int *)calloc(N, sizeof(int));
    }
    return mat;
}

/* Helper to free a dynamic 2D array */
void free_matrix(int **mat, int N) {
    for (int i = 0; i < N; i++) {
        free(mat[i]);
    }
    free(mat);
}

/* Verifies if two matrices are identical */
int verify_result(int **mat1, int **mat2, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat1[i][j] != mat2[i][j]) return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <matrices.txt> <num_threads>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int num_threads = atoi(argv[2]);

    if (num_threads <= 0) {
        fprintf(stderr, "Error: num_threads must be a positive integer.\n");
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening matrix file");
        return 1;
    }

    int N;
    if (fscanf(file, "%d", &N) != 1) {
        fprintf(stderr, "Error reading matrix size.\n");
        fclose(file);
        return 1;
    }

    int **A = allocate_matrix(N);
    int **B = allocate_matrix(N);
    int **C_naive = allocate_matrix(N);
    int **C_pthread = allocate_matrix(N);
    int **C_clone = allocate_matrix(N);

    // Read Matrix A
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(file, "%d", &A[i][j]);
        }
    }

    // Read Matrix B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(file, "%d", &B[i][j]);
        }
    }
    fclose(file);

    struct timeval start, end;
    long t_naive, t_pthread, t_clone;

    // 1. Naive Benchmark
    gettimeofday(&start, NULL);
    compute_naive(N, A, B, C_naive);
    gettimeofday(&end, NULL);
    t_naive = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);

    // 2. Pthread Benchmark
    gettimeofday(&start, NULL);
    compute_pthread(N, A, B, C_pthread, num_threads);
    gettimeofday(&end, NULL);
    t_pthread = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);

    // 3. Clone Benchmark
    gettimeofday(&start, NULL);
    compute_clone(N, A, B, C_clone, num_threads);
    gettimeofday(&end, NULL);
    t_clone = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);

    // Verification step
    int pthread_ok = verify_result(C_naive, C_pthread, N);
    int clone_ok = verify_result(C_naive, C_clone, N);

    printf("\n==================================================\n");
    printf("BENCHMARK RESULTS (Matrix: %dx%d | Threads: %d)\n", N, N, num_threads);
    printf("==================================================\n");
    printf("1. Naive (Sequential): %ld us\n", t_naive);
    printf("2. POSIX Pthreads:     %ld us  [Verification: %s]\n", t_pthread, pthread_ok ? "PASS" : "FAIL");
    printf("3. Linux clone():      %ld us  [Verification: %s]\n", t_clone, clone_ok ? "PASS" : "FAIL");
    printf("==================================================\n");

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C_naive, N);
    free_matrix(C_pthread, N);
    free_matrix(C_clone, N);

    return 0;
}