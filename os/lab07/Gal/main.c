#include "vmem_nru.h"

void simulator(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening addresses file");
        exit(1);
    }
    init_paga_table();
    init_frames();
    int clock = 0;
    int total_accesses = 0;
    char line[50];
    char *end;

    printf("CLOCK INTERRUPT: Resetting R bits");
    uint32_t logical_addr;

    while (fgets(line, sizeof(line), file))
    {
        if(clock ==10){
            reset_R_bit();
            clock=0;
        }
        if (line[0] == '\n' || line[0] == '#')
            continue;
        logical_addr = (uint32_t)strtoul(line, &end, 10);
        // making sure there are no spaces
        while (*end == ' ')
        {
            end++;
        }
        // extracting the bit
        char op = *end;

        access_memory(logical_addr,op);
        total_accesses++;

        clock++;
    }

    printf("Total Accesses: %d | Total Page Faults: %d | Total Disk Writting: %d\n",total_accesses,faults,modified);
}

int main(int argc, char *argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <addresses_file.txt>\n", argv[0]);
        return 1;
    }
    simulator(argv[1]);
}