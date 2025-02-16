#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <memory>
#include <cstring>
#include <thread>
#include <mutex>
#include "socket.hpp"

class Manager{
public:
    Manager(int port);
    void add_new_client();
    void close_sockets();
    void check_connections();
    void handle_receiver(std::shared_ptr<Socket> client);
    void join_threads();

    void print_client_status(std::shared_ptr<Socket>& client);
    void print_counters();

    //getters and setters
    std::vector<std::shared_ptr<Socket>>& get_clients() { return clients; };
private:
    static constexpr size_t buffer_size = 1024;
    std::vector<std::shared_ptr<Socket>> clients;
    int current_port;
    std::mutex mutex;
};

#endif