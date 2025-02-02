#include "socket.hpp"

int Socket::create_socket()
{
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
        status = -1;
    }
    else{
        status = 0;
    }

    return status;
}

int Socket::socket_options()
{
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
        status = -1;
    }
    else {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        status = 0;
    }

    return status;
}

int Socket::bind_socket()
{
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
        status = -1;
    }
    else{
        status = 0;
    }

    return status;
}

int Socket::listen_socket()
{
    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
        status = -1;
    }
    else{
        status = 0;
    }

    return status;
}

int Socket::accept_socket()
{
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept");
        exit(EXIT_FAILURE);
        status = -1;
    }
    else{
        status = 0;
    }

    return status;
}