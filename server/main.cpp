#include <iostream>
#include <cstring>
#include <thread>
#include <csignal>

#include "socket.hpp"
#include "manager.hpp"

Manager* global_manager = nullptr;

void signal_handler(int signum) {
    if (global_manager) {
        global_manager->print_counters();
    }

    std::exit(signum);
}


int main() {
    constexpr size_t port = 8080;
    Manager manager(port);

    global_manager = &manager;
    std::signal(SIGINT, signal_handler);

    while(true){
        manager.check_connections();
    }

    manager.close_sockets();
    return 0;
}
