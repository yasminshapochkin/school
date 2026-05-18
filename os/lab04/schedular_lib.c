#include "scheduler_lib.h"
#include <stdbool.h>
#include <stdlib.h>
void simulate_fcfs(Process proc[], int n)
{
    for (int i = 0; i < n; i++)
    {
        proc[i].remaining_time = proc[i].burst_time;
    }

    int T = 0;
    int indexNextProc = 0;
    int runningProcess = -1;

    while (proc[n - 1].is_completed == 0)
    {
        if (T >= proc[indexNextProc].arrival_time)
        {
            runningProcess = indexNextProc;
            indexNextProc++;
            T += proc[runningProcess].burst_time;
            proc[runningProcess].finish_time = T;
            proc[runningProcess].is_completed = 1;
            proc[runningProcess].turnaround_time = proc[runningProcess].finish_time - proc[runningProcess].arrival_time;
            proc[runningProcess].waiting_time = proc[runningProcess].turnaround_time - proc[runningProcess].burst_time;
        }
        else
        {
            T++;
        }
    }
}

void simulate_sjf(Process proc[], int n)
{
    for (int i = 0; i < n; i++)
    {
        proc[i].remaining_time = proc[i].burst_time;
    }

    int T = 0;
    int finished = 0;

    while (finished < n)
    {
        int nextProcess = -1;
        for (int i = 0; i < n; i++)
        {
            if (!proc[i].is_completed && T >= proc[i].arrival_time)
            {
                if (nextProcess == -1 || proc[i].burst_time < proc[nextProcess].burst_time)
                {
                    nextProcess = i;
                }
            }
        }

        if (nextProcess == -1)
        {
            T++;
            continue;
        }

        T += proc[nextProcess].burst_time;
        nextProcess = -1;
        finished++;
        proc[nextProcess].is_completed = 1;
        proc[nextProcess].finish_time = T;
        proc[nextProcess].turnaround_time = proc[nextProcess].finish_time - proc[nextProcess].arrival_time;
        proc[nextProcess].waiting_time = proc[nextProcess].turnaround_time - proc[nextProcess].burst_time;
    }
}

void simulate_rr(Process proc[], int n, int quantum)
{
    for (int i = 0; i < n; i++)
    {
        proc[i].remaining_time = proc[i].burst_time;
    }

    int T = 0;
    bool RQ[n];

    for (int i = 0; i < n; i++)
        RQ[i] = false;

    int runningProcess = -1;
    int finished = 0;

    while (finished < n)
    {
        for (int i = 0; i < n; i++)
        {

            if (T >= proc[i].arrival_time)
            {
                RQ[i] = true;
            }
        }
        if (runningProcess == -1)
        {
            for (int i = 0; i < n; i++)
            {
                if (RQ[i])
                {
                    runningProcess = i;
                    RQ[i] = false;
                    break;
                }
            }
        }
        if (runningProcess == -1)
        {
            T++;
            continue;
        }
        int runT;
        if (proc[runningProcess].remaining_time > quantum)
            runT = quantum;
        else
            runT = proc[runningProcess].remaining_time;

        proc[runningProcess].remaining_time -= runT;
        T += runT;
        if (proc[runningProcess].remaining_time == 0)
        {
            RQ[runningProcess] = false;
            finished++;
            proc[runningProcess].is_completed = 1;
            proc[runningProcess].finish_time = T;
            proc[runningProcess].turnaround_time = proc[runningProcess].finish_time - proc[runningProcess].arrival_time;
            proc[runningProcess].waiting_time = proc[runningProcess].turnaround_time - proc[runningProcess].burst_time;
            int stop = runningProcess;
        }
        while (!RQ[runningProcess++])
        {
            runningProcess %= i;
            if (runningProcess == stop)
            {
                runningProcess = -1;
            }
        }
    }
}

        void simulate_srt(Process proc[], int n)
        {
            for (int i = 0; i < n; i++)
            {
                proc[i].remaining_time = proc[i].burst_time;
            }

            int T = 0;
            bool RQ[n];
            for (int i = 0; i < n; i++)
            {
                RQ[i] = false;
            }
            int i = 0;
            int nextProcess = -1;
            int finished = 0;

            while (finished < n)
            {
                nextProcess = -1;
                while (i < n && T >= proc[i].arrival_time)
                {
                    RQ[i] = true;
                    i++;
                }

                for (int j = 0; j < i; j++)
                {

                    if (!RQ[j])
                    {
                        continue;
                    }
                    if (nextProcess == -1)
                    {
                        nextProcess = j;
                    }
                    else if (proc[j].remaining_time < proc[nextProcess].remaining_time)
                    {
                        nextProcess = j;
                    }
                }
                proc[nextProcess].remaining_time--;
                T++;

                if (proc[nextProcess].remaining_time == 0)
                {
                    finished++;
                    RQ[nextProcess] = false;
                    proc[nextProcess].is_completed = 1;
                    proc[nextProcess].finish_time = T;
                    proc[nextProcess].turnaround_time = proc[nextProcess].finish_time - proc[nextProcess].arrival_time;
                    proc[nextProcess].waiting_time = proc[nextProcess].turnaround_time - proc[nextProcess].burst_time;
                }
            }
        }
