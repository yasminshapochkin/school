#include "scheduler_lib.h"
#include <stdbool.h>
#include <stdlib.h>
void simulate_fcfs(Process proc[], int n)
{
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
    }
}

void simulate_sjf(Process proc[], int n)
{
    int T = 0;
    int RQ[n];
    int i = 0;
    int nextProcess = -1;
    int finished = 0;

    while (finished < n)
    {
        if (T < proc[i].arrival_time)
        {
            RQ[i] = i;
            i++;
        }
        if (nextProcess == -1)
        {
            for (int j = 0; j < i; j++)
            {
                int index = RQ[j];
                if (index == -1)
                {
                    continue;
                }
                if (nextProcess == -1)
                {
                    nextProcess = index;
                }
                else if (proc[index].burst_time < proc[nextProcess].burst_time)
                {
                    nextProcess = index;
                }
            }

            T += proc[nextProcess].burst_time;
            nextProcess = -1;
            finished++;
            RQ[nextProcess] = -1;
            proc[nextProcess].is_completed = 1;
            proc[nextProcess].finish_time = T;
            proc[nextProcess].turnaround_time = proc[nextProcess].finish_time - proc[nextProcess].arrival_time;
            proc[nextProcess].waiting_time = proc[nextProcess].turnaround_time - proc[nextProcess].burst_time;
        }
    }
}

void simulate_rr(Process proc[], int n, int quantum)
{

    int T = 0;
    bool RQ[n];
    int i = 0;
    int runningProcess = -1;
    int finished = 0;

    while (finished < n)
    {
        if (T < proc[i].arrival_time && i < n)
        {
            RQ[i] = true;
            if (runningProcess == -1)
                runningProcess = i;
            i++;
        }
        T++;
        RQ[runningProcess] = false;
        finished++;
        proc[runningProcess].is_completed = 1;
        proc[runningProcess].finish_time = T;
        proc[runningProcess].turnaround_time = proc[runningProcess].finish_time - proc[runningProcess].arrival_time;
        proc[runningProcess].waiting_time = proc[runningProcess].turnaround_time - proc[runningProcess].burst_time;
        int stop = runningProcess;
        while (!RQ[runningProcess++])
        {
            runningProcess %= i;
            if (runningProcess == stop)
            {
                runningProcess = -1;
                break;
            }
        }
        if (proc[runningProcess].remaining_time == 0)
        {
            RQ[runningProcess] = false;
            finished++;
            proc[runningProcess].is_completed = 1;
            proc[runningProcess].finish_time = T;
            proc[runningProcess].turnaround_time = proc[runningProcess].finish_time - proc[runningProcess].arrival_time;
            proc[runningProcess].waiting_time = proc[runningProcess].turnaround_time - proc[runningProcess].burst_time;
        }
        int stop = runningProcess;
        while (!RQ[runningProcess++])
        {
            runningProcess %= i;
            if (runningProcess == stop)
            {
                runningProcess = -1;
                break;
            }
        }
    }
}

void simulate_srt(Process proc[], int n)
{
    int T = 0;
    bool RQ[n];
    int i = 0;
    int nextProcess = -1;
    int finished = 0;

    while (finished < n)
    {
        if (T < proc[i].arrival_time)
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
            else if (proc[index].burst_time < proc[nextProcess].burst_time)
            {
                nextProcess = index;
            }
        }


        if(proc[nextProcess])       
        finished++;
        RQ[nextProcess] = false;
        proc[nextProcess].is_completed = 1;
        proc[nextProcess].finish_time = T;
        proc[nextProcess].turnaround_time = proc[nextProcess].finish_time - proc[nextProcess].arrival_time;
        proc[nextProcess].waiting_time = proc[nextProcess].turnaround_time - proc[nextProcess].burst_time;
    }
}
