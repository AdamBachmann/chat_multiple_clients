#include <iostream>
#include <cstring>
#include <thread>

#include "socket.hpp"
#include "manager.hpp"

int main() {
    constexpr size_t port = 8080;
    Manager manager(port);

    while(true){
        manager.check_connections();
    }
    manager.close_sockets();
    return 0;
}
