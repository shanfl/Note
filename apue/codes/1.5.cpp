#include <unistd.h>
#include <string.h>
#define BUFFSIZE 4096
int main(){
    int n;
    char buff[BUFFSIZE];
    while((n=read(STDIN_FILENO,buff,BUFFSIZE)) > 0){
        if(write(STDOUT_FILENO,buff,n)!=n){
            char*err = "error on write\n";
            write(STDERR_FILENO,err,strlen(err));
        }
    }

    return 0;
}