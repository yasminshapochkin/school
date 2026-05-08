#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char *argv[] ){
    if(argc <2){
        return 1;
    }
    pid_t pid = fork();
    
    if (pid == 0){
        execlp( argv[1] , argv[1]  , NULL );
    }
    wait(NULL);
    printf("Parent: execution complete.");

    return 0;



}