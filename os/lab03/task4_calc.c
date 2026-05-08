#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    if (argc < 3){
        return 1;
    }
    int num1=atoi(argv[1]);
    int num2=atoi(argv[2]);

    pid_t pids1=fork();
    
    if(pids1==0){
        int sum=num1+num2;
        printf("Child 1 (Sum): %d + %d = %d\n",num1,num2,sum);
        exit(sum);
    }
    else if (pids1>0)
    {
        int status;
        waitpid(pids1,&status,0);
        int s=WEXITSTATUS(status);
        printf("Parent: Child 1 result was %d\n",s);
    }
    

    pid_t pids2= fork();
    
    if(pids2==0){
        int mul=num1*num2;
        printf("Child 1 (Mul): %d * %d = %d\n",num1,num2,mul);
        exit(mul);
    }else if (pids2>0)
    {
        int status;
        waitpid(pids2,&status,0);
        int s=WEXITSTATUS(status);
        printf("Parent: Child 2 result was %d\n",s);
    }
    printf("All computations done");

    return 0;

}
