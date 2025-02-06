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
    Manager(int port) : current_port(port) { add_new_client(); };
    int add_new_client();
    int get_port(){ return current_port; };
    std::vector<std::unique_ptr<Socket>> get_clients() { return clients; };
private:
    int current_port;
    std::vector<std::unique_ptr<Socket>> clients;
};