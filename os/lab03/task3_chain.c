#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// yungest son finishes first father last!

int main(int argc, char *argv[] ){
    if(argc <2){return 1;}
    int num = atoi(argv[1]);
    
    for(int i = 0 ; i < num ; i++){

        pid_t pid = fork();
        if(pid > 0 ){
            wait(NULL);
            break;}

    }
    
    printf("Process[%d],my parent is [%d]\n", getpid(), getppid());

    return 0;

}