#ifndef MATRIX_BENCH_H
#define MATRIX_BENCH_H


/*  Structure for Thread Argumrnts  */

typedef struct {
    int start_row;  //The first row this thread is responsible for
    int end_row;    //The last row this thread is responsible for
    int size;       // N (matrix dimention)
    int **A;        // pointer to global matrix A
    int **B;        // pointer to global matrix B
    int **C;        // pointer to global matrix C
} ThreadData;


#define STACK_SIZE (1024 * 1024) // 1MB stack

/*Prototypes for the 3 compation methods*/
void compute_naive(int N, int **A , int **B, int **C);
void compute_pthread(int N, int **A , int **B, int **C, int num_threads );
void compute_clone(int N, int **A , int **B, int **C, int num_threads );

/* Prototypes for the worker function */
void* multiply_worker_pthread(void* arg);
int multiply_worker_clone(void* arg);



#endif