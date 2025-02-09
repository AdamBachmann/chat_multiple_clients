#include "manager.hpp"

Manager::Manager(int port) : current_port(port)
{
    add_new_client();
}

void Manager::add_new_client(){
    std::cout << "Port: " << current_port << std::endl;
    std::unique_ptr<Socket> client = std::make_unique<Socket>(current_port);
    client->create_socket();
    print_client_status(client);
    client->socket_options();
    print_client_status(client);
    client->bind_socket();
    print_client_status(client);
    client->listen_socket();
    print_client_status(client);
    client->accept_socket();
    print_client_status(client);

    std::string message {"SERVER:: moja wiadomosc powitalna"};
    send(client->get_new_socket(), message.c_str(), message.length(), 0);
    
    std::thread receive_thread(&Manager::handle_receiver,this, client->get_new_socket());
    std::scoped_lock sl(mutex);
    client->set_receive_thread(receive_thread);
    
    clients.push_back(std::move(client));

    std::string message2 {"SERVER:: DRUGA"};
    send(clients[0]->get_new_socket(), message2.c_str(), message2.length(), 0);

    ++current_port;
}

void Manager::close_sockets()
{
    int number_of_clients = clients.size();
    std::scoped_lock sl(mutex);
    for(int i = 0; i < number_of_clients; ++i) {
        clients.at(i)->close_socket();
    }
}

void Manager::print_client_status(std::unique_ptr<Socket>& client)
{
    auto status = client->get_status();
    std::cout << "Status = ";
    switch(status)
    {
        case 0:  std::cout << "NO_ERROR ";  break;
        case 1:  std::cout << "WRONG_STATE ";   break;
        case 2:  std::cout << "INIT_ERROR ";    break;
        case 3:  std::cout << "WAITING_FOR_CREATE ";    break;
        case 4:  std::cout << "CREATE_ERROR ";  break;
        case 5:  std::cout << "WAITING_FOR_OPTIONS ";   break;
        case 6:  std::cout << "OPTIONS_ERROR "; break;
        case 7:  std::cout << "WAITING_FOR_BIND ";  break;
        case 8:  std::cout << "BIND_ERROR ";    break;
        case 9:  std::cout << "WAITING_FOR_LISTENING "; break;
        case 10: std::cout << "LISTEN_ERROR ";  break;
        case 11: std::cout << "WAITING_FOR_ACCEPT ";    break;
        case 12: std::cout << "ACCEPT_ERROR ";  break;
        case 13: std::cout << "WAITING_FOR_CONNECTION ";    break;
        case 14: std::cout << "CONNECTED "; break;
    }
    std::cout << std::endl;
}

void Manager::check_connections()
{
    int counter = 0;
    int all_clients = clients.size();
    for(int i = 0; i < all_clients; ++i){
        if(clients.at(i)->get_status() == CONNECTED){
            ++counter;
        }
    }

    std::cout << "Counter = " << counter << " All clients = " << all_clients << std::endl;
    if(counter == all_clients){
        add_new_client();
    }
}

void Manager::handle_receiver(int socket)
{
    char buffer[buffer_size];
    while (true) {
        memset(buffer, 0, buffer_size);
        //std::scoped_lock sl(mutex); TODO
        int valread = read(socket, buffer, buffer_size);
        if (valread > 0) {
            std::cout << "Klient: " << buffer << std::endl;
        }
    }
}

void Manager::join_threads()
{
    int number_of_clients = clients.size();
    for(int i = 0; i < number_of_clients; ++i){
        clients.at(i)->get_receive_thread().join();
    }
}