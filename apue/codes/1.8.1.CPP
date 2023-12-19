#include <unistd.h>
#include <iostream>
int main(){
    std::cout << "uid:" <<getuid() << ",gid:" <<getgid() <<"\n";
    return 0;
}