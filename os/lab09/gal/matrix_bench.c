#define _GNU_SOURCE
#include <pthread.h>
#include<stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#include "matrix_bench.h"

void *multiply_worker_pthread(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    for (int i = data->start_row; i < data->end_row; i++)
    {
        for (int j = 0; j < data->size; j++)
        {
            data->C[i][j] = 0;

            for (int k = 0; k < data->size; k++)
                data->C[i][j] += data->A[i][k] * data->B[k][j];
        }
    }
    return NULL;
}

int multiply_worker_clone(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    for (int i = data->start_row; i < data->end_row; i++)
    {
        for (int j = 0; j < data->size; j++)
        {
            data->C[i][j] = 0;

            for (int k = 0; k < data->size; k++)
                data->C[i][j] += data->A[i][k] * data->B[k][j];
        }
    }
    return 0;
}

void compute_naive(int N, int **A, int **B, int **C)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void compute_pthread(int N, int **A, int **B, int **C, int num_threads)
{

    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * num_threads);
    ThreadData *data = (ThreadData *)malloc(sizeof(ThreadData) * num_threads);
    int numRows = N / num_threads;
    int res = N % num_threads;

    int row_Sindex = 0;
    int row_Eindex = numRows;
    for (int i = 0; i < num_threads; i++)
    {
        if (res > 0)
        {
            row_Eindex++;
            res--;
        }
        data[i].start_row = row_Sindex;
        data[i].end_row = row_Eindex;
        data[i].size = N;
        data[i].A = A;
        data[i].B = B;
        data[i].C = C;
        pthread_create(&threads[i], NULL, multiply_worker_pthread, &data[i]);
        row_Sindex = row_Eindex;
        row_Eindex += numRows;
    }
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i],NULL);

    free(threads);
    free(data);
}

void compute_clone(int N, int **A, int **B, int **C, int num_threads)
{
    pid_t *PIDs = (pid_t *)malloc(sizeof(pid_t) * num_threads);
    char **stacks = (char **)malloc(num_threads * sizeof(char *));
    ThreadData *data = (ThreadData *)malloc(sizeof(ThreadData) * num_threads);
    int numRows = N / num_threads;
    int res = N % num_threads;

    int row_Sindex = 0;
    int row_Eindex = numRows;
    for (int i = 0; i < num_threads; i++)
    {
        if (res > 0)
        {
            row_Eindex++;
            res--;
        }
        data[i].start_row = row_Sindex;
        data[i].end_row = row_Eindex;
        data[i].size = N;
        data[i].A = A;
        data[i].B = B;
        data[i].C = C;

        row_Sindex = row_Eindex;
        row_Eindex += numRows;

        stacks[i] = malloc(STACK_SIZE);
        char *stack_top = stacks[i] + STACK_SIZE;
        PIDs[i] = clone(multiply_worker_clone, stack_top, CLONE_VM | CLONE_FILES | SIGCHLD, &data[i]);
    }
    for (int i = 0; i < num_threads; i++)
        waitpid(PIDs[i], NULL, 0);
    for (int i = 0; i < num_threads; i++)
        free(stacks[i]);
    free(stacks);
    free(PIDs);
    free(data);
}