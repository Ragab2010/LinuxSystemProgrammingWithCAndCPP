/*
*  udpchoclient_unconnected.cpp: Client program connects to the echo
*  service running on the ubuntuserver having ip 127.0.0.1
*  at port 7, sends a string and receives the same string
*  and display it on stdout
*  compile: gcc udpechoclient_unconnected.c -o udpechoclient_unconnected
*  usage: ./udpechoclient_unconnected <ip> 7
*/

#include<iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>




#define REMOTE_ADRR "127.0.0.1"

using namespace std;

int main(int argc , char **argv){
    
    if(argc != 3){
        cerr<<"Must enter IP and port of echo server\n"<<endl;
        return 1;
    }
    //*** STEP-I:  Create socket for the client
    int client_socket_fd = socket(AF_INET ,SOCK_DGRAM , 0 );
    if(client_socket_fd == -1){
        cerr<<"server_socket_fd creation failed "<<endl;
        return 2;
    }

    //*** STEP-II: Populate Socket's DS for remote IP and Port, and
    //***          let the local IP and Port be selected by the OS itself
    struct sockaddr_in destination_addr;
    destination_addr.sin_family=AF_INET;
    destination_addr.sin_port = htons(atoi(argv[2]));
    int ip_convert_stauts = inet_aton(argv[1] , &destination_addr.sin_addr);
    if(ip_convert_stauts ==0){
        cerr<<"ip conversion from decimal to binary network failed "<<endl;
        return 3;
    }
    memset(&(destination_addr.sin_zero) , 0 , sizeof(destination_addr.sin_zero));
    

    //*** STEP-III:  Client reads string from stdin and send it to udp server
    //***           then read string returned by server and display on stdout
    while(1){
        char buff1[128]={0} ;
        //read string from STDIN and write to server socket 
        int n_stdin = read(STDIN_FILENO , buff1 , sizeof(buff1));
        buff1[n_stdin] = '\0';
        // write(client_socket_fd , buff1 , n_stdin+1);
        sendto(client_socket_fd ,buff1 , sizeof(buff1) ,0, ( struct sockaddr * ) & destination_addr, sizeof(destination_addr) );

        // Read string from socket and write to STDOUT
        char buff2[128]={0} ;
        socklen_t destination_addr_len = sizeof(destination_addr);
        int n_socket = recvfrom(client_socket_fd, buff2, sizeof(buff2), 0, (struct sockaddr *)&destination_addr, &destination_addr_len);
        if (n_socket == -1) {
            cerr << "recvfrom failed" << endl;
            return 4;
        }

        write(STDOUT_FILENO , buff2 , sizeof(buff2));
    }

    //*** STEP-IV:  Close socket
    close(client_socket_fd);

    return 0;
}