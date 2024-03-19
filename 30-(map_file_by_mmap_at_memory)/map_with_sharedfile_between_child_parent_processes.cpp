/*
*  Program mmaps an entire file in its address space
*  and then do a fork, both the child and parent
*  displays contents of file on stdout
*  usage: ./map_with_sharedfile_between_child_parent_processes
*/

#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>




using namespace std;

int main(){
    //open f1.txt
    auto fd = open("./f1.txt" , O_RDONLY);
    if(fd == -1){
        cerr<<"there is an problem  with opening txt file "<<endl;
        return 1; 
    }

    //calculate the size of the file into bytes
    //off_t lseek(int fd, off_t offset, int whence);
    /*
    The first parameter specifies the file descriptor
    The second parameter is offset
    The third parameter specifies the from where we start the offset
    return:the number of the byte (character) it seek
    */
    //int file_size = lseek(fd , 0 , SEEK_END);
    struct stat statbuf;
    fstat(fd , &statbuf);
    int file_size = statbuf.st_size;

    //memory map the file content
    /*
    The first parameter (nullptr) To choose the  kernel  select  the  address of memory map at the address space of this process 
    
    */
    char * file_ptr =(char *) mmap(nullptr , file_size , PROT_READ , MAP_SHARED , fd , 0);
    if(file_ptr == nullptr){
        cerr<<"mmap creation failed"<<endl;
        return 1;
    }
    auto cpid = fork();
    if(cpid == 0){
        cout<<"Child access memory mapped file:\n"<<file_ptr<<endl;
        munmap(file_ptr, file_size);
        close(fd);
        exit(0);
    }else{
        wait(nullptr);
        cout<<"Parent access memory mapped file:\n"<<file_ptr<<endl;
        munmap(file_ptr, file_size);
        close(fd);
        exit(0);
    }
    return 0;
}