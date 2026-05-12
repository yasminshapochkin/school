#include "sceduler_lib"
#include <bool.h>
// is completed = 0 - not 
// 1 - it is
#proccece arr is sorted by arrival Time
#2nd num time of work
void simulate_fcfs(Process proc[], int n){
    int T = 0;
    //int RQ[n];
    bool CPUFree = true;
    //int Runnin_procces = 0;
    int index_RQ_pull = 0;
    int index_RQ_push = 0;
    int runninNow = 0;
    
    
    while(proc[n-1] == 0){
        if (CLOCK >= proc[Process_index].arrival_time){
            index_RQ_push ++;
        }
        if(CPUFree && Runnin_procces[index_RQ_pull].arrival_time <= T){
            
            Runnin_procces[index_RQ_pull].waiting_time = T;
            Runnin_procces[index_RQ_pull].remaining_time--;
            CPUFree = false;
            runninNow = index_RQ_pull;
            index_RQ_pull ++;
            
        }
        else{
            Runnin_procces[index_RQ_pull].remaining_time--;
            if(Runnin_procces[runninNow].remaining_time ==0 ){
                Runnin_procces[index_RQ_pull].finish_time = T;
                Runnin_procces[index_RQ_pull].is_completed = 1;

            }
        }
        T++;

    }


}

void simulate_sjf(Process proc[], int n){
    int T = 0;
    int NUMBER_PROCESS_DONE = 0;
    int RUNNING_PROCESS = 0 ;

    while(NUMBER_PROCESS_DONE < n){
        
        int time_left = -1;
        for(int i = 0; i <n ; i ++){
            if (proc[i].arrival_time <= T && proc[i].is_completed != 0 ){
                if (time_left < proc[i].remaining_time){
                    RUNNING_PROCESS = i;
                }
            }
        }
        T += proc[i].remaining_time;
        proc[i].remaining_time == 0;
        NUMBER_PROCESS_DONE++;

    }


}

void simulate_rr(Process proc[], int n, int quantum){
    float Process_Time_Chunk = 0;
    int RQ[n];
    int index_RQ_pull = 0;
    int index_RQ_push = 0;
    float T = 0;


    while(true){
        

    }


}

void simulate_srt(Process proc[], int n){


}
