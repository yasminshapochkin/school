#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[] ){
    if(argc <3){return 1;}
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    

    pid_t pids1 = fork();
    if(pids1 == 0){
        int sum = num1+num2;
        printf("Child 1 (sum): %d + %d = %d\n", num1, num2 , sum);
        exit(sum);

    }else{
        int status1;
        waitpid(pids1, &status1,0);
        int s = WEXITSTATUS(status1);
        printf("Parent: child 1 result was %d\n", s );

    }
    pid_t pids2 = fork();
    if(pids2 == 0){
        int mul = num1*num2; 
        printf("Child 2 (mul): %d * %d = %d\n", num1, num2 , mul);
        exit(mul);

    }
    int status2;
    waitpid(pids2, &status2,0);
    int s = WEXITSTATUS(status2);
    printf("Parent: child 2 result was %d\n", s );
    printf("All computations done\n" );

    return 0;

}