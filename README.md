# System Programming on Linux

Welcome to the System Programming on Linux repository! This repository contains a variety of code examples covering different topics in system programming on the Linux platform. Each directory represents a different topic, and within each directory, you'll find relevant code examples along with demonstrations captured in GIF format to showcase the execution of the code.

## Table of Contents

1. [08_(atexit)_(on_exit)](#08-atexit-on_exit)
2. [09_(Command_Line_Arguments)_(Environment_Variables)](#09-command_line_arguments-environment_variables)
3. [11_(Implement_UNIX_more_utility)](#11-implement_unix_more_utility)
4. [13_(chmod_chown_dup_dup2_umask)](#13-chmod_chown_dup_dup2_umask)
5. [14_(Implement_UNIX_ls_utility)](#14-implement_unix_ls_utility)
6. [26_(pipe)_(unidirectional_and_bidirectional)](#26-pipe-unidirectional_and_bidirectional)
7. [27_(named_pipe_FIFO)](#27-named_pipe_FIFO)
8. [28_(message_queue)](#28-message_queue)
9. [29_(ipc_shared_memory)](#29-ipc_shared_memory)
10. [30-(map_file_by_mmap_at_memory)](#30-map_file_by_mmap_at_memory)
11. [34_(tcp_echo_server)](#34-tcp_echo_server)
12. [35_(udp_echo_server)](#35-udp_echo_server)
13. [36_(unixDomain_tcp)_(unixDomain_udp)](#36-unixDomain_tcp_unixDomain_udp)
14. [37_(handle_multiple_clients)](#37-handle_multiple_clients)
15. [files](#files)
16. [random_examples](#random_examples)


---

## 08_(atexit)_(on_exit)
This directory explores the usage of `atexit()` and `on_exit()` functions in C/C++ for handling cleanup operations before program termination.

**Contents:**
- `atexit_ex1.cpp`: Example demonstrating the usage of `atexit()` function.
- `atexit_ex2.cpp`: Another example showcasing `atexit()` usage.
- `on_exit_ex.cpp`: Example illustrating the usage of `on_exit()` function.

![atexit_on_exit](08_(atexit)_(on_exit)/atexit_on_exit.gif)

## 09_(Command_Line_Arguments)_(Environment_Variables)
This directory covers handling command-line arguments and environment variables in C/C++.

**Contents:**
- `cmdarg.cpp`: Example for handling command-line arguments.
- `print_environmentVariables.cpp`: Example demonstrating printing environment variables.
- `print_path_and_shell_from_environmentVariables.cpp`: Example to print path and shell from environment variables.

![cmd_env](09_(Command_Line_Arguments)_(Environment_Variables)/cmd_env.gif)

## 11_(Implement_UNIX_more_utility)
This directory implements additional utilities inspired by Unix commands.

**Contents:**
- `morev3.cpp`, `morev4.cpp`, `morev5.cpp`, `morev6.cpp`, `morev7.cpp`: Examples of the `more` utility with different functionalities.
- `pipe_string.cpp`: Example demonstrating string pipelining.

![show_morev7](11_(Implement_UNIX_more_utility)/show_morev7.gif)

## 13_(chmod_chown_dup_dup2_umask)
This directory covers file permission management (`chmod`), ownership management (`chown`), file duplication (`dup`, `dup2`), and setting file creation mask (`umask`).

**Contents:**
- `chmod_file.cpp`: Example demonstrating `chmod` usage.
- `chown.cpp`: Example illustrating `chown` usage.
- `dup.cpp`, `dup2_stdin.cpp`: Examples for file duplication.
- `umask.cpp`: Example demonstrating setting file creation mask.

![chmod_chown_dup_dup2_umask](13_(chmod_chown_dup_dup2_umask)/chmod_chown_dup_dup2_umask.gif)

## 14_(Implement_UNIX_ls_utility)
This directory implements functionalities similar to the `ls` command in Unix.

**Contents:**
- (`lsv0.cpp`, `lsv1.cpp`, ...) Examples  of showcasing different functionalities of `ls`.
- `readdir.cpp`: Example illustrating directory reading.

![Implement_UNIX_ls_utility](14_(Implement_UNIX_ls_utility)/execute_ls_utility.gif)

## 26_(pipe)_(unidirectional_and_bidirectional)
This directory covers unidirectional and bidirectional communication using pipes.

**Contents:**
- `unidirectional_pipe_between_parent_child_processes.cpp`: Example of Use a pipe between two related processes, child is a reader process while parent is a writer process.
- `bidirectional_pipe_between_parent_child_processes.cpp`: Example of Bidirectional communication using two pipes between two related processes, Parent writes first and child reads, Child writes later and parent reads.
- `simple_unidirectional_pipe.cpp`: Example of a pipe shows the usage of a pipe withing a single process.
- `perform_cat_f1.txt_|_wc.cpp`: Example of *  A program that simulate following shell command: `cat f1.txt | wc -l`.

![pipe_communication](26_(pipe)_(unidirectional_and_bidirectional)/pipe_execution_program.gif)

## 27_(named_pipe_FIFO)
This directory explores named pipes (FIFO) and their usage for inter-process communication.

**Contents:**
- `/use_fifo_with_unrelated_process_unidirectionalwrite_process.cpp `: Example of creates a named pipe, myfifo and opens it in write mode and  gets input from user and continuously writes in myfifo.
- `/use_fifo_with_unrelated_process_unidirectionalread_process.cpp`: Example of opens myfifo in read mode and continuously reads from it and displays the characters read on stdout as well.

![named_pipe_FIFO](27_(named_pipe_FIFO)/use_fifo_with_unrelated_process_unidirectional/unidirectional_FIFO.gif)

- `/use_fifo_with_unrelated_process_biodirection/teacher_process.cpp `: Example of creates two named pipes, pipe_for_teacher_sends and pipe_for_teacher_receives , reads from pipe_for_teacher_receives and then writes to the pipe_for_teacher_sends.
- `use_fifo_with_unrelated_process_biodirection/student_process.cpp`: Example of writes to a named pipe (pipe_for_teacher_receives) and then reads from another named pipe (pipe_for_teacher_sends).

![named_pipe_FIFO](27_(named_pipe_FIFO)//use_fifo_with_unrelated_process_biodirection/biodirection_FIFO.gif)

## 28_(message_queue)
This directory covers inter-process communication using message queues.

**Contents:**
- `sender.cpp `: Examples of creates a message queue, and sends two messages in that queue then terminate.
- `receiver.cpp `: Examples of gets the id of an existing message queue, and reads a message from that queue and display the mtext on stdout then terminate.

![message_queue](28_(message_queue)/message_queue.gif)

## 29_(ipc_shared_memory)
This directory covers inter-process communication using shared memory.

**Contents:**
- `writer.cpp `: Examples of creates sharing memory segment and gets a string from user and write that to the shared memory segment then detach it and exits.
- `reader.cpp `: Examples of gets the id of an existing shared memory segment and attach it to its address space
,read the data and display it on stdout then detach the shared memory segment and deletes it.

![ipc_shared_memory](29_(ipc_shared_memory)/shared_memory.gif)

## 30-(map_file_by_mmap_at_memory)
This directory demonstrates memory mapping of files using `mmap()`.

**Contents:**
- `map_txtfile_at_memeory_by_mmap.cpp `Examples of mapping the files  f1.txt  into memory and manipulating them.
- `map_with_sharedfile_between_child_parent_processes.cpp `Examples of mapping the files  f1.txt  into memory and do a fork, both the child and parent displays contents of file on stdout
- `writeTo_txtfile_by_mmap.cpp `Examples of create files  f2.txt and mapping it  into memory then write at the map and do sync.

![map_file_by_mmap](30-(map_file_by_mmap_at_memory)/map_txtfile.gif)

## 34_(tcp_echo_server)
This directory implements a TCP echo server.

**Contents:**
- (`tcpechoserver.cpp `, `tcpechoclient.cpp`): Example of a TCP echo server and client.

![tcp_echo_server](34_(tcp_echo_server)/tcpserver_echo_with_netstat.gif)
- Tcp 3way HandShake and 4-way Connection Termination.

![tcp_echo_server](34_(tcp_echo_server)/tcp_3way_HandShake_and_4-way_Connection_Termination.gif)
## 35_(udp_echo_server)
This directory implements a UDP echo server.

**Contents:**
- (`udpechoclient_connected.cpp `, `udpechoclient_unconnected.cpp`,`udpechoclient_unconnected.cpp`): Example of a UDP echo server and client.

![udp_echo_server](35_(udp_echo_server)/udpserver_echo.gif)

## 36_(unixDomain_tcp)_(unixDomain_udp)
This directory covers communication using Unix domain sockets for TCP and UDP protocols.

**Contents:**
- (`unixdomain_tcpechoclient.cpp `, `unixdomain_tcpechoserver.cpp`): Examples of TCP bidirectional communication using Unix domain sockets.

![unixDomain_communication](36_(unixDomain_tcp)_(unixDomain_udp)/unixDomain_tcp/echo_unixDomain_tcp.gif)

- (`unixdomain_udpreceiver.cpp.cpp `, `unixdomain_udpsender.cpp`): Examples of udp  unidirectional communication using Unix domain sockets.

![unixDomain_communication](36_(unixDomain_tcp)_(unixDomain_udp)/unixDomain_udp/echo_unixdomain_udp.gif)


## 37_(handle_multiple_clients)
This directory focuses on handling multiple clients in a server-client architecture.

**Contents:**
- `tcpechoclient.cpp`: Client code for TCP echo server.
- `tcpechoserver_mutiple_connection_fork.cpp`: TCP echo server handling multiple connections using fork.
- `tcpechoserver_mutiple_connection_pthread.cpp`: TCP echo server handling multiple connections using detached pthread.
- `tcpechoserver_mutiple_connection_select.cpp`: TCP echo server handling multiple connections  by do multiplexing on all descriptors ,  receives a string from client and will send it back to client.
- `tcpechoserver_mutiple_connection_stdthread.cpp`: TCP echo server handling multiple connections using detached std::thread.

![tcpechoserver_mutiple_connection_fork](37_(handle_multiple_clients)/tcpechoserver_mutiple_connection_fork.gif)

![tcpechoserver_mutiple_connection_pthread](37_(handle_multiple_clients)/tcpechoserver_mutiple_connection_pthread.gif)

## files
This directory contains miscellaneous file-related examples.

**Contents:**
- Various file-related examples such as reading files and file manipulation.

*(Add descriptions and GIF images for the remaining directories)*

---