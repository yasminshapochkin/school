#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(int argc, char* argv[]){
    if(argc<3){
        return 0;
    }
    long int mod = strtol(argv[2] , NULL ,8); 
    if(mod == 0){
        char* err = "Chmod failed.\n";
        write(2 , err,strlen(err));
        return 1;
    }
    if(chmod(argv[1],mod) != 0){
        char* err = "Chmod failed.\n";
        write(2 , err,strlen(err));
        return 1;
    }
    return 0;
}