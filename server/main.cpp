#include <iostream>
#include <cstring>
#include <thread>

#include "socket.hpp"

#define PORT 8080
#define BUFFER_SIZE 1024

void handleReceive(int socket) {
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(socket, buffer, BUFFER_SIZE);
        if (valread > 0) {
            std::cout << "Klient: " << buffer << std::endl;
        }
    }
}

int main() {
    Socket s(PORT);
    s.create_socket();
    s.socket_options();
    s.bind_socket();
    s.listen_socket();
    std::cout << "Serwer nasłuchuje na porcie " << PORT << "..." << std::endl;
    s.accept_socket();

    std::cout << "Połączenie przyjęte." << std::endl;

    std::thread receiveThread(handleReceive, s.get_new_socket());

    while (true) {
        std::string message;
        std::cout << "Serwer: ";
        std::getline(std::cin, message);
        send(s.get_new_socket(), message.c_str(), message.length(), 0);
    }

    receiveThread.join();
    close(s.get_new_socket());
    close(s.get_server_fd());

    return 0;
}
