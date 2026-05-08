#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


// s is sleep, z is zombie  

int main(int argc, char *argv[] ){
    if(argc < 2){return 1;}
    int num = atoi(argv[1]);
    pid_t pid = -2;
    for(int i = 0 ; i < num ; i++){
        pid = fork();
        if(pid == 0 ){
            sleep(rand()%5); 
            printf("child %%ld exiting", getpid());
            exit(0);
        }
    }
    system("ps -l");
    printf("Parent: Reviewing process state (look for <defunc>)", getpid());
    for(int i = 0 ; i<num ; i++){
        wait(NULL);
    }
    printf("Parent: all children reaped\n");
    return 0;



}