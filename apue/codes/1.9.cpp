#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>
#include <iostream>

static void sig_int(int);


#define MAXLINE 1024
int main(){
    char buff[MAXLINE];
    pid_t pid;
    int status;

    if(signal(SIGINT,sig_int) == SIG_ERR){
        fprintf(stderr,"signal error\n");
    }

    while(fgets(buff,MAXLINE,stdin)!=nullptr){
        if(buff[strlen(buff)-1] == '\n')
            buff[strlen(buff)-1] = 0;
        
        if((pid=fork()) < 0){
            fprintf(stderr,"fork error\n");
        }else if(pid == 0) // child
        {
            execlp(buff,buff,nullptr);
            fprintf(stderr,"couldn't execute %s error\n",buff);
            return 0;
        }

        if((pid = waitpid(pid,&status,0))<0){
            perror("watipid error");
        }

        printf("%% ");
    }

    return 0;
}

void sig_int(int signo){
    std::cout << "interrupt signo:" << signo << std::endl;
}