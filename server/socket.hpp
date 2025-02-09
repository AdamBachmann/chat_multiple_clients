#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

enum STATUS{
    NO_ERROR,
    WRONG_STATE,
    INIT_ERROR,
    WAITING_FOR_CREATE,
    CREATE_ERROR,
    WAITING_FOR_OPTIONS,
    OPTIONS_ERROR,
    WAITING_FOR_BIND,
    BIND_ERROR,
    WAITING_FOR_LISTENING,
    LISTEN_ERROR,
    WAITING_FOR_ACCEPT,
    ACCEPT_ERROR,
    WAITING_FOR_CONNECTION,
    CONNECTED
};

class Socket {
public:
    // methods for socket
    Socket(int port_number);
    void create_socket();
    void socket_options();
    void bind_socket();
    void listen_socket();
    void accept_socket();
    void close_socket();

    // getters and setters
    int get_new_socket() { return new_socket; };
    int get_server_fd() { return server_fd; };
    int get_status() { return status; };

private:
    STATUS status;
    int port;
    int server_fd;
    int new_socket;
    struct sockaddr_in address;
    int opt;
    int addrlen;
};

#endif