/*
*  unixdomain_udpsender.cpp: Sends a string to the receiver program
*  via unix domain socket file created by receiver
*  compile: gcc unixdomain_udpsender.cpp -o unixdomain_udpsender
*  usage: ./unixdomain_udpsender
*/

#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>






using namespace std;

int main(){
    
    //*** STEP-I:  Create socket for the client
    int client_socket_fd = socket(AF_UNIX ,SOCK_DGRAM , 0 );
    if(client_socket_fd == -1){
        cerr<<"server_socket_fd creation failed "<<endl;
        return 1;
    }

    //STEP-II *** Populate socket's DS for sockaddr_un type by giving the socket file name
    struct sockaddr_un destination_addr;
    destination_addr.sun_family=AF_UNIX;
    strcpy(destination_addr.sun_path , "./socketfile");
    
    //*** STEP-III: Get a string from user and use sendto() to send that string to the receiver process*/
    char buff1[128]={0};
    int n_stdin = read(STDIN_FILENO , buff1 , sizeof(buff1));
    buff1[n_stdin] = '\0';
    sendto(client_socket_fd ,buff1 , sizeof(buff1) ,0, ( struct sockaddr * ) & destination_addr, sizeof(destination_addr) );


    //*** STEP-IV:  Close socket
    close(client_socket_fd);

    return 0;
}