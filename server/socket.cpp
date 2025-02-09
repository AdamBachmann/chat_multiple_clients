#include "socket.hpp"

Socket::Socket(int port_number) : 
    port(port_number), 
    opt(1),
    status(WAITING_FOR_CREATE)
{
    addrlen = sizeof(sockaddr_in); 
}

void Socket::create_socket()
{
    if(status != WAITING_FOR_CREATE){
        status = WRONG_STATE;
        return;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
        status = CREATE_ERROR;
    }
    else{
        status = WAITING_FOR_OPTIONS;
    }
}

void Socket::socket_options()
{
    if(status != WAITING_FOR_OPTIONS){
        status = WRONG_STATE;
        return;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
        status = OPTIONS_ERROR;
    }
    else {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        status = WAITING_FOR_BIND;
    }
}

void Socket::bind_socket()
{
    if(status != WAITING_FOR_BIND){
        status = WRONG_STATE;
        return;
    }

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
        status = BIND_ERROR;
    }
    else{
        status = WAITING_FOR_LISTENING;
    }
}

void Socket::listen_socket()
{
    if(status != WAITING_FOR_LISTENING){
        status = WRONG_STATE;
        return;
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
        status = LISTEN_ERROR;
    }
    else{
        status = WAITING_FOR_ACCEPT;
    }
}

void Socket::accept_socket()
{
    if(status != WAITING_FOR_ACCEPT){
        status = WRONG_STATE;
        return;
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept");
        exit(EXIT_FAILURE);
        status = ACCEPT_ERROR;
    }
    else{
        status = CONNECTED;
    }
}

void Socket::close_socket()
{
    close(new_socket);
    close(server_fd);
}