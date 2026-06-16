#include "page_sim.h"
#include <stdlib.h>

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
    fifoSim.size = 0;

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


