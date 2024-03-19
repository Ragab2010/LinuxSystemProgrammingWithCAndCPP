#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <dirent.h>

// Receives one or more directory names via command line arguments and list their contents. If no argument is passed display the contents of pwd
/* don't show the . 
*  lsv2.c:
*  usage: ./a.out 
        ./a.out dirpath
        ./a.out dir1 dir2 dir3
*/

extern int errno;
void do_ls(const char *);

int main(int argc , char ** argv) {
    if(argc == 1 ){
        // std::cout<<"Enter exactly one argument (a directory name).\n";
        do_ls(".");
        // return 1;
    }
    int i = 0;
    while(++i <argc){
        std::cout<<"Directory listing of "<<argv[i]<<":\n";
        do_ls(argv[i]);
    }
    
    return 0;
}

void do_ls(const char * dirName){
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
            if(entry->d_name[0] =='.')
                continue;
            std::cout<<entry->d_name<<" \n";
            //printf("%s   ",entry->d_name);
        }
    }
    closedir(home_dir);
    std::cout<<std::endl;
}
