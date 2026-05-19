#include "scheduler_lib.h"
#include <stdbool.h>
#include <stdio.h>


// is completed = 0 - not 
// 1 - it is
//proccece arr is sorted by arrival Time
//2nd num time of work
/*maybe ready lab idk man*/


void simulate_fcfs(Process proc[], int n){
    int T = 0;

    
    int might_be_ready = 0;
    
    // reseting the remainin time 
    for(int i = 0 ; i <n ; i++){
        proc[i].remaining_time = proc[i].burst_time;
    }

    
    while (proc[n-1].is_completed == 0){
        // if the next process isnt ready time jump by 1
        if (proc[might_be_ready].arrival_time > T){
            T++;
            continue;
        }
        else{
            // update time
            T += proc[might_be_ready].remaining_time;
            // update remainin time
            proc[might_be_ready].remaining_time = 0;
            // udate finish time
            proc[might_be_ready].finish_time = T;
            // update that this one is completed
            proc[might_be_ready].is_completed = 1;
            // upadte the waiting time he waited 
            proc[might_be_ready].waiting_time = T - proc[might_be_ready].arrival_time;
            // moving the pointing index
            might_be_ready++;

        }
    

    }
  



}

void simulate_sjf(Process proc[], int n){
    
    int T = 0;
    int NUMBER_PROCESS_DONE = 0;
    int RUNNING_PROCESS = 0 ;

    // reseting the remaining time 
    for(int i = 0 ; i <n ; i++){
        proc[i].remaining_time = proc[i].burst_time;
    }

    while(NUMBER_PROCESS_DONE < n){
        int time_left = -1;
        for(int i = 0; i <n ; i ++){
            if (proc[i].arrival_time <= T && proc[i].is_completed != 1 ){
                if(time_left == -1){
                    RUNNING_PROCESS = i;
                    time_left = proc[i].remaining_time;
                }
                if (time_left  > proc[i].remaining_time){
                    RUNNING_PROCESS = i;
                    time_left = proc[i].remaining_time;
                }
                
            }
        }
        // T add to it how much it worked 
        T += proc[RUNNING_PROCESS].remaining_time ; 
        // update remainin time
        proc[RUNNING_PROCESS].remaining_time = 0;
        // update how many finished
        NUMBER_PROCESS_DONE++;
        // update finish time
        proc[RUNNING_PROCESS].finish_time = T ;
        // update that this one is completed
        proc[RUNNING_PROCESS].is_completed = 1;
        // upadte the waiting time he waited 
        proc[RUNNING_PROCESS].waiting_time = T - proc[RUNNING_PROCESS].arrival_time;
        //printf ("%d %d %d %d %d %d %d \n" , T ,proc[RUNNING_PROCESS].remaining_time ,  NUMBER_PROCESS_DONE ,proc[RUNNING_PROCESS].finish_time, proc[RUNNING_PROCESS].is_completed ,proc[RUNNING_PROCESS].waiting_time ,RUNNING_PROCESS);

    }
 
  


}

void simulate_rr(Process proc[], int n, int quantum){
    
    int Process_Time_Chunk = 0;
    int might_be_ready = 0 ;
    int actually_running = 0 ;
    int T = 0;
    int NUMBER_PROCESS_DONE=0;

    // reseting the remaining time 
    for(int i = 0 ; i < n ; i++){
        proc[i].remaining_time = proc[i].burst_time;
    }
    while(NUMBER_PROCESS_DONE < n ){

        // if who might be ready didnt arrive yet we go to the back of the RQ
        if(proc[might_be_ready].arrival_time > T || might_be_ready == n ){
            
            // we run over the RQ candidates 
            actually_running = -1;
            for(int i = 0 ; i < might_be_ready ; i++){
              
                
                // if this process is done then it ignores this i 
                if(proc[i].is_completed == 1 ){
                    continue;
                }
                else{
                    // update to know who will run rn
                    actually_running = i;
                    // stop the for loop
                    break;
                }
                
            }
            // if no process is ready rn so we will jump by 1
            if(actually_running == -1){
               // if(NUMBER_PROCESS_DONE == n-1){break;}
                T++;
                continue;
            }
            
        }
        else{
            // if he is ready the we run him
            actually_running = might_be_ready;
            might_be_ready += might_be_ready == n ? 0 : 1; 
        }
     
        // calc if process needs 2 or 1 time chunks
        Process_Time_Chunk = proc[actually_running].remaining_time >= quantum ? quantum : proc[actually_running].remaining_time;

        // decrees from the process remaining work time
        proc[actually_running].remaining_time -=  Process_Time_Chunk;

        // update the time
        T += Process_Time_Chunk;

        // if the process finished
        if(proc[actually_running].remaining_time == 0 ){
            // update the processes that are finished
            NUMBER_PROCESS_DONE++;
            // update that this one finished
            proc[actually_running].is_completed = 1;
            // update finish time
            proc[actually_running].finish_time = T ;
            // update the waiting time
            proc[actually_running].waiting_time = T - proc[actually_running].arrival_time - proc[actually_running].burst_time;

        }

    }
       
}

void simulate_srt(Process proc[], int n){
    
    int T = 0;
    int NUMBER_PROCESS_DONE = 0;
    int might_be_ready = 0;
    int actually_running = 0;
    // reseting the remaining time 
    for(int i = 0 ; i <n ; i++){
        proc[i].remaining_time = proc[i].burst_time;
    }
    // main loop 
    while (NUMBER_PROCESS_DONE < n){
        
        // if new proc joined make sure its not a finished one
        if(proc[might_be_ready].arrival_time <=T && proc[might_be_ready].is_completed != 1 ){
            // if the new one has less or the same work time 
            if( proc[might_be_ready].remaining_time <= proc[actually_running].remaining_time ){


                // update whos gonna run
                actually_running = might_be_ready;
                // move the index pointer to the next that might be ready
                might_be_ready++;
                // skip the loop incase 2 proc joined at the same time
                continue;
            }
        }
        // upadte time
        T++;
        // update the remaining time for proc
        proc[actually_running].remaining_time--;
        // if the process finished
        if(proc[actually_running].remaining_time == 0 ){
            // update the processes that are finished
            NUMBER_PROCESS_DONE++;
            // update that this one finished
            proc[actually_running].is_completed = 1;
            //upadte FINISH TIME
            proc[actually_running].finish_time = T ;

            // update the waiting time
            proc[actually_running].waiting_time = T - proc[actually_running].arrival_time - proc[actually_running].burst_time;
            // go back to the start of the RQ
            for(int i = 0 ; i <  n ; i++){
                // if this proc isnt done pick him to run and break the loop
                if(proc[i].is_completed !=1 ){
                    actually_running = i;
                    break;
                }
            }
        
        }

       

    }



}
