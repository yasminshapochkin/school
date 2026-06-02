#include "vmem_nru.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void run_simulation(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening addresses file");
        exit(1);
    }
    char line[50];
    uint32_t vir_addr;
    int CLOCK_UPDATE = 10;
    int time = 0;
    printf("CLOCK INTERRUPT: resetting R bits\n");
    init_page_table();
    init_frames();
    
    while (fgets(line, sizeof(line), file)) {

        // see if time to reset thr R bit
        if(time % CLOCK_UPDATE == 0){
            resset_R_bit();
        }

        char *end;
        // get the virtual addres
        vir_addr = (uint32_t)strtoul(line, &end, 10);

        // making sure there are no spaces
        while (*end == ' ') {
            end++;
        }
        //extracting the bit 
        char op = *end;
        access_memory(vir_addr , op);


        time++;
        
    }

    int faults = get_page_faults();
    int diskW = get_disk_writes();
    printf("Total Accesses: %d | Total Faults: %d | Total Disk writes: %d \n" , time , faults ,diskW );

    
}

int main(int argc, char *argv[]) {
    

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <addresses_file.txt>\n", argv[0]);
        return 1;
    }
    
    run_simulation(argv[1]);
    return 0;
}
