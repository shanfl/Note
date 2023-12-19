#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#define MAXLINE 1024
int main(){
    char buff[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    while(fgets(buff,MAXLINE,stdin) != nullptr){
        if(buff[strlen(buff) - 1] == '\n'){
            buff[strlen(buff) - 1] = 0;
        }

        if((pid=fork()) < 0){
            fprintf(stderr,"fork error\n");
        }
        else if(pid == 0) // child
        {
            execlp(buff,buff,(char*)0);
            fprintf(stderr,"coundn't execute %s",buff);
            exit(127);
        }
        /*parent*/
        if((pid = waitpid(pid,&status,0)) < 0){
            fprintf(stderr,"waitpid error");
        }

        printf("%% ");

        int err = errno;
    }
}

//https://stackoverflow.com/questions/21558937/i-do-not-understand-how-execlp-works-in-linux
