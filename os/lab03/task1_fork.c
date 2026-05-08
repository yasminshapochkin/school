#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
/// ex 5 can also do sleep for father , zombe is im done dad isnt , we want son zombie sleep to dad , main goal sons are in zoombie

int main(){
    int x = 100;
    pid_t pid = fork();
    
    if(pid == 0){
        x += 50;
    }
    else{ wait(NULL);}
    printf("My PID is %d : x=%d\n", getpid(), x);
    return 0;


}