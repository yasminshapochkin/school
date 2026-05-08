#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    if (argc < 2){
        return 1;
    }
    int N = atoi(argv[1]);
    for(int i=0;i<N;i++){
        pid_t pid=fork();
        if(pid>0){
            wait(NULL);
            break;
        }
    }
    printf("Process [%ld],my parent is [%ld] .",getpid(),getppid());
    return 0;
}