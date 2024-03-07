#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fcntl.h> // if you are using constant O_RDONLY


// ls -l
/* don't show the . 
*  lsv2.c:
*  usage: ./a.out 
        ./a.out dirpath
        ./a.out dir1 dir2 dir3
*/

extern int errno;

void do_ls(const char *);
void file_type(const char *fname , struct stat * buf){
    // struct stat buf;
    // if (lstat(fname, &buf)<0){
    //     perror("Error in stat");
    //     exit(1);
    // }
    if ((buf->st_mode &  0170000) == 0010000) 
            printf("%s is a Named Pipe\n", fname);
    else if ((buf->st_mode &  0170000) == 0020000) 
            printf("%s is a Character Special file\n", fname);
    else if ((buf->st_mode &  0170000) == 0040000) 
            printf("%s is a Directory\n", fname);
    else if ((buf->st_mode &  0170000) == 0060000) 
            printf("%s is a Block Special file\n", fname);
    else if ((buf->st_mode &  0170000) == 0100000) 
            printf("%s is a Regular file\n", fname);
    else if ((buf->st_mode &  0170000) == 0120000) 
            printf("%s is a Soft link\n", fname);
    else if ((buf->st_mode &  0170000) == 0140000) 
            printf("%s is a Socket\n", fname);
    else 
            printf("Unknwon mode\n");

}
void show_stat_info(const char *fname){
    struct stat info;
    int rv = lstat(fname, &info);
    if (rv == -1){
        perror("stat failed");
        exit(1);
    }
    // printf("mode: %o\n", info.st_mode);
    file_type(fname ,&info );
    printf("link count: %ld\n", info.st_nlink);
    printf("user: %d\n", info.st_uid);
    printf("group: %d\n", info.st_gid);
    printf("size: %ld\n", info.st_size);
    printf("modtime: %ld\n", info.st_mtime);
    printf("name: %s\n", fname );
}

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
            //std::cout<<entry->d_name<<" \n";
            show_stat_info(entry->d_name);
            std::cout<<std::endl;

            //printf("%s   ",entry->d_name);
        }
    }
    closedir(home_dir);
    std::cout<<std::endl;
}
