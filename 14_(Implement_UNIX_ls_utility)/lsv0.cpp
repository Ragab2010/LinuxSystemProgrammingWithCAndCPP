#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <dirent.h>

extern int errno;
void do_ls(char *);

int main(int argc , char ** argv) {
    if(argc != 2){
        std::cout<<"Enter exactly one argument (a directory name).\n";
        return 1;
    }
    std::cout<<"Directory listing of "<<argv[1]<<":\n";
    do_ls(argv[1]);
    



    return 0;
}

void do_ls(char * dirName){
    DIR *  home_dir = opendir(dirName);
    if(home_dir ==NULL){
        // exit(1);
        std::cerr<<"Cannot open directory:"<<dirName<<'\n';
        return ;
    }
    struct dirent *entry; 
    while((entry =readdir(home_dir)) != NULL){
        if(entry == NULL && errno != 0){
            perror("readdir failed");
            exit(errno);
        }else{
            std::cout<<entry->d_name<<"   "<<std::endl;
            //printf("%s   ",entry->d_name);
        }
    }
    closedir(home_dir);
}
