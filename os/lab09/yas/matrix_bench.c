// for the p thread library so it will compile 
// give to Makefile the p thread

#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "matrix_bench.h"


void compute_naive(int N, int **A , int **B, int **C){
    for (int i = 0 ; i < N ; i++ ){
        for (int j = 0; j < N ; j++ ){
            C[i][j] = 0;
            for (int k = 0 ; k < N ;k++ ){
                C[i][j] += A[i][k]*B[k][j];
            }

        }
        
    }
}


// the aray aint global 
void compute_pthread(int N, int **A , int **B, int **C, int num_threads ){
    // 1 dynamically allocate 
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    ThreadData *tData = malloc(num_threads * sizeof(ThreadData));
    
    int row_per_thread = N / num_threads;
    int residue = N % num_threads ; 
    // for start row
    int row_Sindex = 0;
    // for end row
    int row_Eindex = row_per_thread; 

    for (int i = 0 ; i < num_threads ; i++){
        if(residue != 0){
            row_Eindex++;
            residue--;
        }
        tData[i].start_row = row_Sindex ;
        tData[i].end_row = row_Eindex ;
        tData[i].size = N;
        tData[i].A = A;
        tData[i].B = B;
        tData[i].C = C;
        row_Sindex = row_Eindex;
        row_Eindex += row_per_thread;

        pthread_create(&threads[i], NULL , multiply_worker_pthread, &tData[i]);

    }
    for (int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }
    free(threads);
    free(tData);

}

/* flags -> 

    CLONE_VM | CLONE_FILES | SIGCHLD 

*/ 
void compute_clone(int N, int **A , int **B, int **C, int num_threads ){
    pid_t *PIDS = malloc(num_threads * sizeof(pid_t));
    ThreadData *tData = malloc(num_threads * sizeof(ThreadData));
    char **STACKS = malloc(num_threads * sizeof(char*)); ///

    int row_per_thread = N / num_threads;
    int residue = N % num_threads ; 
    // for start row
    int row_Sindex = 0;
    // for end row
    int row_Eindex = row_per_thread; 
    for (int i = 0 ; i < num_threads ; i++){
        if(residue != 0){
            row_Eindex++;
            residue--;
        }
        tData[i].start_row = row_Sindex ;
        tData[i].end_row = row_Eindex ;
        tData[i].size = N;
        tData[i].A = A;
        tData[i].B = B;
        tData[i].C = C;
        row_Sindex = row_Eindex;
        row_Eindex += row_per_thread;
        STACKS[i] = malloc(STACK_SIZE);
        char *stack_top = STACKS[i] + STACK_SIZE;
        PIDS[i] = clone(multiply_worker_clone, stack_top, CLONE_VM | CLONE_FILES | SIGCHLD ,&tData[i] );

    }
    for (int i = 0 ; i< num_threads ; i++){
        waitpid(PIDS[i],NULL,0);
    }
    for (int i = 0 ; i< num_threads ; i++){
        free( STACKS[i]);
    }
    free(STACKS);
    free(tData);
    free(PIDS);
    

}



/*workers methods
    very similar 
    casts pointer to threadData* and calcs matrix C values  
*/
void* multiply_worker_pthread(void* arg){
    // c[i][j] = sum A[i][k]*B[k][i] 
    ThreadData* tData = (ThreadData*)arg;
    for (int i = tData->start_row ; i < tData->end_row ;i++ ){

        for (int j = 0; j < tData->size ; j++ ){
            tData->C[i][j] = 0;
            for (int k = 0 ; k < tData->size ; k++ ){
                tData->C[i][j] += tData->A[i][k]*tData->B[k][j];
            }

        }
        
    }
    return NULL;
}



int multiply_worker_clone(void* arg){
    multiply_worker_pthread(arg);
    return 0;
}
