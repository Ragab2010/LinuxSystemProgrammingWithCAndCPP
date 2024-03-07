#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <dirent.h>


int main() {
    const char *dirName = "/home";
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
            printf("\nEnd of directory\n");
            return 0;
        }
        printf("%s   ",entry->d_name);
    }
    closedir(home_dir);


    return 0;
}
