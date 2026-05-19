#import "memory_manager.h"


Segment *init_memory(int total_size)
{
    Segment *memory;
    memory->is_process = 1;
    memory->process_id = -1;
    memory->start_address = 0;
    memory->size = total_size;
    memory->next = NULL;
    return memory;
}


void print_memory(Segment *head){
    Segment* temp = head;
    str ar = ["P1","H"];
    while(temp){
        if(temp.is_process == 1){
            printf("[H,")
        }
        else{
            printf("P1,")
        }
        printf("[addr:%d,Size:%d]",temp.start_address , temp.size);
        printf("->");
        temp = temp->next;

    }
    printf("NULL");


}

void print_stats(Segment *head){
    //int total_memory = 0;
    int total_proc = 0;
    int total_holes = 0;
    int total_proc_m = 0;
    int total_hole_m = 0;
  //  int total_nodes = 0;
    Segment* temp = head;
    while(temp){
    
// memory is taken it is a process
        if(temp.is_process == 0 ){
            total_proc++;
            total_proc_m += temp.size;
        }
        else{
            total_holes++;
            total_hole_m = temp.size;
        }
        temp = temp.next;
    }

   
    printf("--- Memory Statistics ---\n");
    printf("Total Memory: %d units\n" ,(total_proc_m + total_hole_m) );
    float precent_umemory =  ( (total_proc_m / (total_proc_m +total_hole_m))*100)  ;
    printf("Used Memory: %d units (%f)\n" , total_proc_m , precent_umemory );

    float precent_fmemory =  ( (total_hole_m / (total_proc_m +total_hole_m))*100)  ;
    printf("Free Memory: %d units (%f)\n" , total_hole_m , precent_fmemory );

    printf("Number of Segments: %d (%d Processes, %d holes)\n",(total_proc+total_holes), total_proc,total_holes );
    printf("-------------------------");


}

/*
 * הקצאת זיכרון בשיטת First Fit.
 * יש למצוא את החור הראשון שמתאים, לבצע פיצול (Splitting) במידת הצורך ולעדכן את הרשימה.
 * החזרה: מצביע לראש הרשימה המעודכן.
 */
Segment* allocate_first_fit(Segment *head, int process_id, int size){
    Segment* temp = head;
    int m_adress = 0;

    while(temp){
        if(temp->is_process == 1 && temp->size >= size){
            if(temp->size== size){
                temp->is_process = 0;
                temp->process_id = process_id ;
            }
            else{
                // i want to add the proc after the temp
                temp->size -= size;
                 // create a node 
                Segment* new = malloc(sizeof(Segment));
                if (!new_seg) {return head; }
                //update adress
                new->m_adress = temp->m_adress + temp->size;
                // update proc 
                new->is_process = 0;
                // update its next
                new->next = temp->next;
                //size
                new->size = size;
                //id
                new->process_id = process_id ;       

            }
            break;
           
            
        
        }
        else{
            m_adress += temp->size;
            temp = temp->next;
        }


    }
    // need to print to the err channel!
    printf("Out of Memory");
    return head;

}


// --- משימה 3: אלגוריתם Best Fit ---

/*
 * הקצאת זיכרון בשיטת Best Fit.
 * יש לסרוק את כל הרשימה, למצוא את החור הקטן ביותר שמתאים, לבצע פיצול ולעדכן.
 * החזרה: מצביע לראש הרשימה המעודכן.
 */
Segment* allocate_best_fit(Segment *head, int process_id, int size){
    int memory_best_node = 0;
    int index = 0;

//NEED A FLAG HERE
    int best_m_size = -1;
    int best_m_diff = 0;
    Segment* temp = head;

    while(temp){
        // its a hole and has the size
        if(temp->is_process == 1 && temp->size >= size){
            // calc diff!
            
            if( best_m_size < 0 || temp->size-size < best_m_diff ){
                best_m_size = temp->size;
                best_m_diff = temp->size - size;
                memory_best_node = index;
                
            }
            // if perfect match then no need to keep on searching 
            if(temp->size-size == 0){break;}

        }// on to the next node
        temp = temp->next;
        index++;


    }// -- end of loop
    temp = head;
    // find the best node again
    for(int i = 0 ; i<memory_best_node ; i++){
        temp = temp->next;
    }

    if(temp->size== size){
        temp->is_process = 0;
        temp->process_id = process_id ;
    }
    else{
        // i want to add the proc after the temp
        temp->size -= size;
        // create a node 
        Segment* new = malloc(sizeof(Segment));

        if (!new_seg) {
            return head; 
             //update adress
            new->m_adress = temp->m_adress + temp->size;
            // update proc 
            new->is_process = 0;
            // update its next
            new->next = temp->next;
             //size
            new->size = size;
            //id
            new->process_id = process_id ;       

        }

        // need to print to the err channel!
    printf("Out of Memory");
    
    return head;

}
// proc releaser
Segment* deallocate_mem(Segment *head, int process_id){
    Segment* temp = head;
    Segment* to_delete;
// main loop 
    while(temp){
        // if we are insize the process id we wanted 
        if(temp->process_id == process_id){
            //if its next is a hole
            if(temp->next->is_process == 1){
            // we take the next of next to not lose the list 
                Segment* next_te = temp->next->next;
            //update its size
                temp->size += temp->next->size;
            //free the memory of who we wanted
                free(temp->next);
            //updating the new next process
                temp->next = next_te;

            }


        }
        //see if the next is the one we want and the one before it is a hole
        else if(temp->next->process_id == process_id && temp->is_process == 1){
            // we take the next of next to not lose the list 
            Segment* next_te = temp->next->next;
            //update its size
            temp->size += temp->next->size;
            // leave the id of who we wanted to terminate
            temp->process_id = temp->next->process_id;
            //free the memory of who we wanted
            free(temp->next);
            //updating the new next process
            temp->next = next_te;


        }
        // here gonna make the freeing and connecting


        //move to the next
        temp = temp->next;

    }
    return head;


    
}

