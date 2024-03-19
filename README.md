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
14. [files](#files)
15. [random_examples](#random_examples)

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
- Examples (`lsv0.cpp`, `lsv1.cpp`, ...) showcasing different functionalities of `ls`.
- `readdir.cpp`: Example illustrating directory reading.

## 26_(pipe)_(unidirectional_and_bidirectional)
This directory covers unidirectional and bidirectional communication using pipes.

**Contents:**
- `bidirectional_comm_pipe_fork.cpp`: Example of bidirectional communication using pipes.
- `simple_unidirectional_pipe.cpp`: Example of unidirectional pipe communication.

![pipe_communication](26_(pipe)_(unidirectional_and_bidirectional)/pipe_communication.gif)

## 27_(named_pipe_FIFO)
This directory explores named pipes (FIFO) and their usage for inter-process communication.

**Contents:**
- Examples of using FIFO with unrelated processes in bidirectional, unidirectional, and C++ scenarios.

![named_pipe_FIFO](27_(named_pipe_FIFO)/named_pipe_FIFO.gif)

## 28_(message_queue)
This directory covers inter-process communication using message queues.

**Contents:**
- Examples of sending and receiving messages between processes using message queues.

![message_queue](28_(message_queue)/message_queue.gif)

## 29_(ipc_shared_memory)
This directory covers inter-process communication using shared memory.

**Contents:**
- Examples of sharing memory segments between processes using shared memory.

![ipc_shared_memory](29_(ipc_shared_memory)/ipc_shared_memory.gif)

## 30-(map_file_by_mmap_at_memory)
This directory demonstrates memory mapping of files using `mmap()`.

**Contents:**
- Examples of mapping files into memory and manipulating them.

![map_file_by_mmap](30-(map_file_by_mmap_at_memory)/map_file_by_mmap.gif)

## 34_(tcp_echo_server)
This directory implements a TCP echo server.

**Contents:**
- Example of a TCP echo server and client.

![tcp_echo_server](34_(tcp_echo_server)/tcp_echo_server.gif)

## 35_(udp_echo_server)
This directory implements a UDP echo server.

**Contents:**
- Example of a UDP echo server and client.

![udp_echo_server](35_(udp_echo_server)/udp_echo_server.gif)

## 36_(unixDomain_tcp)_(unixDomain_udp)
This directory covers communication using Unix domain sockets for TCP and UDP protocols.

**Contents:**
- (`unixdomain_tcpechoclient.cpp `, `unixdomain_tcpechoserver.cpp`): Examples of TCP bidirectional communication using Unix domain sockets.
![unixDomain_communication](36_(unixDomain_tcp)_(unixDomain_udp)/unixDomain_tcp/echo_unixDomain_tcp.gif)

- (`unixdomain_udpreceiver.cpp.cpp `, `unixdomain_udpsender.cpp`): Examples of udp  unidirectional communication using Unix domain sockets.
![unixDomain_communication](36_(unixDomain_tcp)_(unixDomain_udp)/unixDomain_udp/echo_unixdomain_udp.gif)


## files
This directory contains miscellaneous file-related examples.

**Contents:**
- Various file-related examples such as reading files and file manipulation.

*(Add descriptions and GIF images for the remaining directories)*

---