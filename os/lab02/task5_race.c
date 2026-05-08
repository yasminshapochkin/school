#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc,char* argv[]){
    if(argc<2){
        return 1;
    }
    pid_t pid=-2;
    int K=atoi(argv[1]);
    for(int i=0;i<K;i++){
        pid=fork();
        if(pid==0){
            sleep(rand() % 5);
            printf("child %ld exiting ...\n",getpid());
            exit(-1);
        }else{
            sleep(NULL);
        }
    }
    int status;
    system("ps -l");
    printf("Parent: Reviewing process state (look for < defunct >)\n");
    for(int i=0; i<K; i++){
        if(pid==0)
            pid=wait(&status);
        
    }
    printf("Parent: all childrem reaped");

    return 0;
}