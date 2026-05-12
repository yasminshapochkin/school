#include "sceduler_lib"
#include <bool.h>
// is completed = 0 - not 
// 1 - it is
//proccece arr is sorted by arrival Time
//2nd num time of work
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
        if(CPUFree && proc[index_RQ_pull].arrival_time <= T){
           // Runnin_procces[index_RQ_pull].waiting_time = T;
            
            CPUFree = false;
            runninNow = index_RQ_pull;
            index_RQ_pull ++;
            
        }
        else{
            T +=  proc[index_RQ_pull].remaining_time; 
            proc[index_RQ_pull].remaining_time = 0;
            proc[index_RQ_pull].finish_time = T;
            proc[index_RQ_pull].is_completed = 1;
            proc[index_RQ_pull].waiting_time = T - proc[index_RQ_pull].arrival_time;

        }

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
                    time_left = proc[i].remaining_time;
                }
                if(time_left == -1){
                    break;
                }
            }
        }
        T += proc[RUNNING_PROCESS].remaining_time;
        proc[RUNNING_PROCESS].remaining_time == 0;
        NUMBER_PROCESS_DONE++;
        proc[RUNNING_PROCESS].finish_time = T;
        proc[index_RQ_pull].is_completed = 1;
        proc[index_RQ_pull].waiting_time = T - proc[index_RQ_pull].arrival_time;

    }


}

void simulate_rr(Process proc[], int n, int quantum){
    int Process_Time_Chunk = 0;
    int might_be_ready = 0;
    int actually_running = 0;
    int index_RQ_pull = 0;
    int index_RQ_push = 0;
    int T = 0;
    int NUMBER_PROCESS_DONE=0

    while(NUMBER_PROCESS_DONE < n){
        if(proc[might_be_ready].arrival_time > T){
            actually_running = 0;
        }
        else{
            actually_running = might_be_ready;
            might_be_ready++;
        }
        for(actually_running ; actually_running < might_be_ready;actually_running++){
            if(proc[actually_running].is_completed != 1 ){
                Process_Time_Chunk = proc[actually_running].remaining_time > 2 ? 2:1;
                proc[actually_running].remaining_time == max(proc[actually_running].remaining_time -2 , 0);
                break;   
             }
        }
        T += Process_Time_Chunk;


        
        

    }


}

void simulate_srt(Process proc[], int n){
    

}
