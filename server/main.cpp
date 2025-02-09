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
    Manager manager;
    manager.add_new_client(PORT);
    std::thread receiveThread(handleReceive, manager.get_clients().at(0)->get_new_socket());

    while(true){
        manager.check_new_client();
    }

    receiveThread.join();
    manager.close_sockets();

    return 0;
}
