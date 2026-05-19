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

    while(temp){
        if(temp.is_process == 1){
            Segment* new ;
            new->next = temp->next;
            



        }




    }

}


// --- משימה 3: אלגוריתם Best Fit ---

/*
 * הקצאת זיכרון בשיטת Best Fit.
 * יש לסרוק את כל הרשימה, למצוא את החור הקטן ביותר שמתאים, לבצע פיצול ולעדכן.
 * החזרה: מצביע לראש הרשימה המעודכן.
 */
Segment* allocate_best_fit(Segment *head, int process_id, int size){}

