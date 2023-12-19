#include <fcntl.h>
#include <stdio.h>
#include <iostream>
int main()
{
    mode_t md;
    int fd = creat("/home/shanfl/shanf.txt",S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IWOTH | S_IROTH);
    if(fd == -1){
        fprintf(stderr,"creat file failed\n");
        perror("create file error");
        return 1;
    }
    
    std::cout << "fd:" << fd << std::endl;

    return 0;
}