#include "manager.hpp"

int Manager::add_new_client(){
    auto client = std::make_unique<Socket>(current_port);
    client->create_socket();
    client->socket_options();
    client->bind_socket();
    client->listen_socket();
    
    clients.push_back(std::move(client));
}