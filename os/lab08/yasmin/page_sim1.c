#include "page_sim.h"
#include <stdlib.h>

struct node_LRU *head;
struct node_LRU *tail;

int run_fifo(int *request, int num_requests, int frame_count)
{
    FIFOStruct fifoSim;
    fifoSim.frames = (int *)malloc(frame_count * sizeof(int));
    if (!fifoSim.frames)
        exit(-1);

    for (int i = 0; i < frame_count; i++)
    {
        fifoSim.frames[i] = -1;
    }

    fifoSim.size = 0;
    fifoSim.first = 0;
    fifoSim.last = 0;
   

    int pf=0;
    for(int i=0; i<num_requests; i++){
        int page = request[i];

        if(!in_frames(fifoSim.frames, page, frame_count)){
            pf++;
            if(fifoSim.size < frame_count){
                fifoSim.frames[fifoSim.last] = page;
                fifoSim.last++;
                fifoSim.last%=frame_count;
                fifoSim.size++;
            }else{
                fifoSim.frames[fifoSim.first] = page;
                fifoSim.first++;
                fifoSim.first%=frame_count;
            }
        }
    }
    free(fifoSim.frames);
    return pf;
}

bool in_frames(int *frames, int page, int frame_count)
{
    for (int i = 0; i < frame_count; i++)
    {
        if (frames[i] == page)
            return true;
    }
    return false;
}


int run_lru(int* request, int num_requests, int frame_count){
    // inisualization
    head = (node_LRU*)malloc(sizeof(node_LRU));
    if (!head){
        exit(-1);
    }
    
    head->frame_number = 0;
    head->page_num = -1;
    head->prev = NULL;
    head->next = NULL;
    tail = head;

    for(int i = 1; i< frame_count; i++){
        node_LRU *temp = malloc(sizeof(node_LRU));
        if (!temp){   exit(-1); }
        temp->frame_number = i;
        temp->page_num = -1;
        tail->next = temp;
        temp->prev = tail;
        temp->next = NULL;
        tail = temp;
    }

    int pf = 0 ;

    for(int i = 0; i<num_requests; i++){
        node_LRU *search = head;
        while(search){
            if(search->page_num == request[i]){
                break;
            }  
            search = search->next;
        }
        // pf
        if(search == NULL){
            pf++;
            // take tail and add to top of list 
            search = tail;

            if(tail->prev){tail->prev->next = NULL;}
            tail = tail->prev;
            search->page_num = request[i];
            tail->next = NULL;
            search->next = head;
            search->prev = NULL;
            head = search;

        }
        else if(search->prev) {
            search->prev->next = search->next;
            if(search->next) search->next->prev = search->prev;
            search->prev = NULL;
            search->next = head;
            if(head) head->prev = search;
            head = search;
        }
        // not
       /* else{
            // what if tail?
            search->prev->next = search->next;
            if(search->next){  search->next->prev = search->prev;  }
            search->prev = NULL;            
            search->next = head;
            if(head) { head->prev = search; }

            head = search;
        }*/

    }
    temp = head;
    while(head){
        node_LRU *temp = head;
        head = head->next;
        free(temp);
    }


    return pf;
}