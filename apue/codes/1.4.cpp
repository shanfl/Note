#include <dirent.h>
#include <iostream>
int main(int argc,char*argv[]){
    DIR *dp;
    struct dirent* pdirent;

    if(argc != 2) {
        std::cout << "usage: ls ?dir?" <<std::endl;
        return 0;
    }

    dp = opendir(argv[1]);
    if(dp == nullptr){
        std::cout << "open dir is failed" <<std::endl;
        return 0;
    }

    while((pdirent = readdir(dp)) != nullptr){
        std::cout << "name:"<<pdirent->d_name << ",type:" << pdirent->d_type << ",ino:" << pdirent->d_ino << "\n";
    }

    closedir(dp);

    return 0;
}