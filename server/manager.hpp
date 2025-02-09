#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <memory>
#include "socket.hpp"

class Manager{
public:
    void add_new_client(int port);
    void check_new_client();
    void close_sockets();

    //getters and setters
    std::vector<std::unique_ptr<Socket>>& get_clients() { return clients; };
private:
    std::vector<std::unique_ptr<Socket>> clients;
};

#endif