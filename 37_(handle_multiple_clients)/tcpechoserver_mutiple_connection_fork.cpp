
/*
*  tcpechoserver_mutiple_connection_fork.cpp: Server programs runs on ubuntu server
*  binds itself to ip localhost and port 54154, 
*  waits for client connections
*  for each client do a fork()
*  receives a string from client
*  and will send it back to client
*  usage: ./tcpechoserver_mutiple_connection_fork
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
#include <sys/wait.h>

#define BACKLOG 10
#define LOCAL_ADDR "127.0.0.1"

using namespace std;

int main() {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    //*** STEP-I:  Create passive socket for the server
    int server_socket_fd = socket(AF_INET ,SOCK_STREAM , 0 );
    if(server_socket_fd == -1) {
        cerr<<"server_socket_fd creation failed "<<endl;
        return 1;
    }
    //*** STEP-II: Create a address structure containing server IP addr
    //***          and port, then bind the server_sockfd with this address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(54154);
    int ip_convert_status = inet_aton(LOCAL_ADDR , &server_addr.sin_addr);
    if(ip_convert_status == 0) {
        cerr<<"ip conversion from decimal to network failed "<<endl;
        return 2;
    }

    memset(&(server_addr.sin_zero) , 0 , sizeof(server_addr.sin_zero));
    int bind_status = bind(server_socket_fd , (const struct sockaddr *) &server_addr , sizeof(server_addr));
    if(bind_status == -1) {
        cerr<<"binding failed "<<endl;
        return 3;
    }

    //*** STEP-IV: Accept a connection, blocks until connection from client is established
    //****         will return a brand new descriptor for comm with this single connection
    int listen_status = listen(server_socket_fd , BACKLOG);
    if(listen_status == -1) {
        cerr<<"listen failed "<<endl;
        return 4;
    }

    while(1) {
        cout<<"\nServer waiting for client connection..."<<endl;
        //*** STEP-IV: Accept a connection, blocks until connection from client is established
        //****         will return a brand new descriptor for comm with this single connection
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket_fd = accept(server_socket_fd , (struct sockaddr *) &client_addr , &client_addr_len);
        if(client_socket_fd == -1) {
            cerr<<"client_socket_fd creation failed "<<endl;
            return 1;
        }

        cout<<"\n********* CLIENT CONNECTION ESTABLISHED ********"<<endl;

        // Fork a new process
        pid_t pid = fork();

        if(pid < 0) {
            cerr << "Fork failed." << endl;
            return 1;
        }

        if(pid == 0) { // Child process
            // Close server socket in child process
            close(server_socket_fd);
        //STEP-V ***** Read from client_socket_fd and write back
            char buf[100];
            int return_value;
            while((return_value = read(client_socket_fd , buf , 100)) > 0) {
                write(client_socket_fd , buf , return_value);
            }

            close(client_socket_fd);
            cout<<"\n********* CLIENT CONNECTION TERMINATED ********"<<endl;
            return 0;
        } else { // Parent process
            // Close client socket in parent process
            close(client_socket_fd);
        }
        
        // Reap terminated child processes
        //signal (int __signal, __sighandler_t __handler)
        signal(SIGCHLD, SIG_IGN); // Ignore SIGCHLD to prevent zombie processes
        /*
        -SIGCHLD :this signal is generated when a child process of a parent process changes state, such as when it terminates or stops.
        -SIG_IGN :is handler that tells the operating system that the parent process will ignore the SIGCHLD signal when it's received.
                    By ignoring the parent process the SIGCHLD signal, it indicates to the operating system that it does not wish to handle the termination of child processes itself.
                    Instead, the operating system automatically reaps the terminated child processes, and they do not remain as zombies in the system's process table.
                    so this will prevents the creation of zombie processes.
        */
    }

    return 0;
}
