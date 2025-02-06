#include <iostream>
#include <cstring>
#include <thread>

#include "socket.hpp"
#include "manager.hpp"

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
    Manager m(PORT);
    int number_of_clients = m.get_clients().size();
    for(int i = 0; i < number_of_clients; i++) {
        auto client = *m.get_clients().at(i);
        
        if(client.get_status() == 0) {
            client.accept_socket();
        }
        else {
            std::cout << "Socket status = " << client.get_status() << std::endl;
        }
    }

    for(int i = 0; i < number_of_clients; i++) {
        std::thread receiveThread(handleReceive, m.get_clients().at(i)->get_new_socket());
    }

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
