#include "manager.hpp"

void Manager::add_new_client(int port){
    auto client = std::make_unique<Socket>(port);
    client->create_socket();
    client->socket_options();
    client->bind_socket();
    client->listen_socket();
    client->accept_socket();

    std::string message {"SERVER:: moja wiadomosc powitalna"};
    send(client->get_new_socket(), message.c_str(), message.length(), 0);
    
    clients.push_back(std::move(client));
}

void Manager::check_new_client()
{
    int number_of_clients = clients.size();
    for(int i = 0; i < number_of_clients; ++i) {
        auto client = *clients.at(i);
        if(client.get_status() == WAITING_FOR_ACCEPT) {
            
        }
    }
}

void Manager::close_sockets()
{
    int number_of_clients = clients.size();
    for(int i = 0; i < number_of_clients; ++i) {
        auto client = *clients.at(i);
        client.close_socket();
    }
}