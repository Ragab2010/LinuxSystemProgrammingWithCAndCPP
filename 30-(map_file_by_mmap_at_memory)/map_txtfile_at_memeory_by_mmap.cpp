#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>




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
    int file_size = lseek(fd , 0 , SEEK_END);

    //memory map the file content
    /*
    The first parameter (nullptr) To choose the  kernel  select  the  address of memory map at the address space of this process 
    
    */
    char * file_ptr =(char *) mmap(nullptr , file_size , PROT_READ , MAP_PRIVATE , fd , 0);
    if(file_ptr == nullptr){
        cerr<<"mmap creation failed"<<endl;
        return 1;
    }

    cout<<"Data in the file is :"<<endl;
    cout<<file_ptr<<endl;

    //Need to free the mapped memory 
    munmap(file_ptr, file_size);
    //munmap does not close the file discriptor, so we need to do that
    close(fd);

    return 0;
}