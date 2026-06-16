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

    int pf = 0;
    for (int i = 0; i < num_requests; i++)
    {
        int page = request[i];

        if (!in_frames(fifoSim.frames, page, frame_count))
        {
            pf++;
            if (fifoSim.size < frame_count)
            {
                fifoSim.frames[fifoSim.last] = page;
                fifoSim.last++;
                fifoSim.last %= frame_count;
                fifoSim.size++;
            }
            else
            {
                fifoSim.frames[fifoSim.first] = page;
                fifoSim.first++;
                fifoSim.first %= frame_count;
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

int run_lru(int *request, int num_requests, int frame_count)
{
    head = (node_LRU *)malloc(sizeof(node_LRU));
    if (!head)
        exit(-1);

    head->frame_number = 0;
    head->page_num = -1;
    head->next = NULL;
    head->prev = NULL;
    tail = head;

    for (int i = 1; i < frame_count; i++)
    {

        node_LRU *temp = malloc(sizeof(node_LRU));
        if (!temp)
            exit(-1);
        temp->frame_number = i;
        temp->next = NULL;
        temp->page_num = -1;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }

    int pf = 0;
    for (int i = 0; i < num_requests; i++)
    {
        int page = request[i];
        node_LRU *search = in_fr_lru(head, page);
        if (search)
        {
            if (search != head)
            {
                node_LRU *prev = search->prev;
                node_LRU *next = search->next;
                prev->next = next;
                if (next)
                    next->prev = prev;
                else
                    tail = prev;

                search->prev = NULL;
                search->next = head;
                head->prev = search;
                head = search;
            }
        }
        else
        {
            pf++;
            search = tail;
            if (tail->prev)
            {
                tail = tail->prev;
                tail->next = NULL;
                search->next = head;
                search->prev = NULL;
                search->page_num = page;
                head->prev = search;
                head = search;
            }
            else
            {
                search->page_num = page;
            }
        }
    }
    while(head){
        node_LRU* temp=head;
        head=head->next;
        free(temp);
    }
    return pf;
}

node_LRU *in_fr_lru(node_LRU *frame, int page)
{
    while (frame)
    {
        if (frame->page_num == page)
            return frame;

        frame = frame->next;
    }
    return NULL;
}