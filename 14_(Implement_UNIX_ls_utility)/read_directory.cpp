/*
*  list all the file that at the directory 
*  usage: ./read_directory /home

*/

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <dirent.h>

using namespace std;
int main(int argc , char **argv) {
    if (argc <2){
        cerr<<"there is no input directory "<<endl;
        return 1;
    }
    const char *dirName = argv[1];
    DIR *  home_dir = opendir(dirName);
    if(home_dir ==NULL){
        return 1;
    }
    struct dirent *entry; 
    while(1){
        entry =readdir(home_dir);
        if(entry == NULL && errno != 0){
            perror("readdir");
            return errno;
        }
        if(entry == NULL && errno == 0){
            cout<<"\nEnd of directory\n";
            return 0;
        }
        cout<<"   "<<entry->d_name<<endl;
    }
    closedir(home_dir);


    return 0;
}
