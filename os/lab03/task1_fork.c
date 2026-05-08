#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(){
    int x=100;
    pid_t pid = fork();
    if (pid ==0){
        x+=50;
        
    }else{
        wait(NULL);
    }
    printf("My PID is %d:x =%d\n",getpid(),x);
    return 0;

};
