/*
*  tcpechoserver.cpp: Server programs runs on local machine
*  binds itself to socketfile in pwd, 
*  waits for client connection
*  receives a string from client
*  and will send it back to client
*  compile: g++ unixdomain_tcpechoserver.cpp -o unixdomain_tcpechoserver
*  usage: ./unixdomain_tcpechoserver
*/

#include<iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/un.h>



//how many pending connections queue  will hold
#define BACKLOG 10 //the size of the pending queue for pending connections


using namespace std;

int main(){

    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;
    //STEP-0 *****Remove any old sockets and create an unnamed socket for the server
    unlink("./socketfile");
    //*** STEP-I:  Create  socket for the server
    int server_socket_fd = socket(AF_UNIX ,SOCK_STREAM , 0 );
    if(server_socket_fd == -1){
        cerr<<"server_socket_fd creation failed "<<endl;
        return 1;
    }

    //STEP-II ****Populate socket's DS for the sockaddr_un type 
    //       by giving the filename and then bind server_sockfd with this file
    
    server_addr.sun_family=AF_UNIX;
    strncpy(server_addr.sun_path ,"./socketfile" , sizeof(server_addr.sun_path)-1);


    int bind_status = bind(server_socket_fd , (const struct sockaddr *) &server_addr , sizeof(server_addr));
    if(bind_status == -1){
        cerr<<"binding failed "<<endl;
        return 2;
    }

    //STEP-III ***Create a connection queue and wait for clients
    int listen_stauts = listen(server_socket_fd , BACKLOG);
    if(listen_stauts ==-1){
        cerr<<"listen failed "<<endl;
        return 3;
    }
    while(1){
        cout<<"\nServer waiting for client connection..."<<endl;
        //*** STEP-IV: Accept a connection, blocks until connection from client is established
        //****         will return a brand new descriptor for comm with this single connection
        socklen_t client_addr_len = sizeof(client_addr);
        int client_sockt_fd = accept(server_socket_fd , (struct sockaddr *) &client_addr , &client_addr_len);
        if(client_sockt_fd == -1){
            cerr<<"client_sockt_fd creation failed "<<endl;
            return 1;
        }
        cout<<"\n********* CLIENT CONNECTION ESTABLISHED ********"<<endl;
        //STEP-V ***** Read from sockfd and write back
        char buf[100];
        int return_value;
        while(return_value = read(client_sockt_fd , buf , sizeof(buf))){
            write(client_sockt_fd , buf , return_value);
        }
        //STEP-VI ***** close client_sockt_fd when client send nothing or close()
        close(client_sockt_fd);
        cout<<"\n********* CLIENT CONNECTION TERMINATED ********"<<endl;

    }

    return 0;
}