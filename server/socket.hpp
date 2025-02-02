#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class Socket
{
public:
    // methods for socket
    Socket(int port_number) : port(port_number), opt(1){ addrlen = sizeof(sockaddr_in);};
    int create_socket();
    int socket_options();
    int bind_socket();
    int listen_socket();
    int accept_socket();

    // getters and setters
    int get_new_socket() { return new_socket; };
    int get_server_fd() { return server_fd; };

private:
    int status;
    int port;
    int server_fd;
    int new_socket;
    struct sockaddr_in address;
    int opt;
    int addrlen;
};