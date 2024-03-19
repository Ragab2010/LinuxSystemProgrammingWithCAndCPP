/*
*  unixdomain_tcpechoclient.cpp: Client programs connects
*  to a unix domain socket file created by server program
*  with the name of socketfile in pwd
*  sends a string and receives the same string
*  and display it on stdout
*  compile: g++ unixdomain_tcpechoclient.cpp -o unixdomain_tcpechoclient
*  usage: ./unixdomain_tcpechoclient
*/

#include<iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>






using namespace std;

int main(){


    //*** STEP-I:  Create socket for the client
    int client_socket_fd = socket(AF_UNIX ,SOCK_STREAM , 0 );
    if(client_socket_fd == -1){
        cerr<<"server_socket_fd creation failed "<<endl;
        return 1;
    }
    //STEP-II *** Populate socket's DS for sockaddr_un type by giving the file name as agreed with the server

    struct sockaddr_un destination_addr;
    destination_addr.sun_family=AF_UNIX;
    strncpy(destination_addr.sun_path ,"./socketfile" , sizeof(destination_addr.sun_path)-1);

    
    //*** STEP-III: Connect this socket to the server's socket
    int connect_status =connect(client_socket_fd , (const struct sockaddr *) &destination_addr , sizeof(destination_addr));
    if(connect_status == -1){
        cerr<<"connect creation failed "<<endl;
        return 1;
    }

    //*** STEP-IV:  Client reads string from stdin and send it to server
    //***           then read string returned by server and display on stdout
    char buff1[128],buff2[128] ;
    while(1){
        //read string from STDIN and write to server socket 
        int n_stdin = read(STDIN_FILENO , buff1 , sizeof(buff1));
        buff1[n_stdin] = '\0';
        write(client_socket_fd , buff1 , n_stdin+1);

        //read string from socket and write to STDOUT
        int n_socket = read(client_socket_fd , buff2 , sizeof(buff2));
        buff2[n_socket] = '\0';
        write(STDOUT_FILENO , buff2 , n_socket+1);
    }

    close(client_socket_fd);

    return 0;
}