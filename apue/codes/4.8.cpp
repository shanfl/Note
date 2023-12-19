#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc,char*argv[]){
    if(argc != 2){
        fprintf(stderr,"usage: a.out <pathname>");
        exit(0);
    }

    if(access(argv[1],R_OK) < 0)
    {
        perror("access error");
        exit(0);
    }else
        fprintf(stderr,"read access ok\n");

    if(open(argv[1],O_RDONLY) < 0)
        perror("open with READONLY error");
    else
        fprintf(stderr,"open for reading ok\n");

    exit(0);
}