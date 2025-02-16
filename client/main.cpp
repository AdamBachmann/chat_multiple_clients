#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

#define PORT 8080
#define BUFFER_SIZE 1024

void handleReceive(int sock) {
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(sock, buffer, BUFFER_SIZE);
        if (valread > 0) {
            std::cout << "Serwer: " << buffer << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;

    // Tworzenie gniazda
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));

    // Konwersja adresu IP serwera
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return -1;
    }

    // Połączenie z serwerem
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    std::cout << "Połączono z serwerem na porcie " << atoi(argv[1]) << std::endl;

    std::thread receiveThread(handleReceive, sock);

    while (true) {
        std::string port = argv[1];
        std::string message = "Port = " + port; 
        //std::string message;
        //std::cout << "Klient: ";
        //std::getline(std::cin, message);
        send(sock, message.c_str(), message.length(), 0);

        usleep(100000); //100ms
    }

    receiveThread.join();
    close(sock);

    return 0;
}
