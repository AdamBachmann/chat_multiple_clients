#include "manager.hpp"

Manager::Manager(int port) : current_port(port)
{
    add_new_client();
}

void Manager::add_new_client(){
    std::shared_ptr<Socket> client = std::make_shared<Socket>(current_port);
    client->create_socket();
    client->socket_options();
    client->bind_socket();
    client->listen_socket();
    client->accept_socket();

    std::string message {"SERVER:: moja wiadomosc powitalna"};
    send(client->get_new_socket(), message.c_str(), message.length(), 0);
    
    std::thread receive_thread(&Manager::handle_receiver,this, client);
    std::scoped_lock sl(mutex);
    client->set_receive_thread(receive_thread);
    
    clients.push_back(client);

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

void Manager::print_client_status(std::shared_ptr<Socket>& client)
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

void Manager::print_counters()
{
    static int previous = 0;
    for(auto i = 0; i < clients.size(); ++i){
        std::cout << "Klient " << i << ": " << clients[i]->get_received_messages_counter() 
            << "\troznica: " << previous - clients[i]->get_received_messages_counter() << std::endl;
        
        previous = clients[i]->get_received_messages_counter();
    }
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

    if(counter == all_clients){
        add_new_client();
    }
}

void Manager::handle_receiver(std::shared_ptr<Socket> client)
{
    char buffer[buffer_size];
    while (true) {
        memset(buffer, 0, buffer_size);
        
        int valread = read(client->get_new_socket(), buffer, buffer_size);
        if (valread > 0) {
            //std::cout << "Klient: " << buffer << std::endl;

            std::scoped_lock sl(mutex);
            int value = client->get_received_messages_counter() + 1;
            client->set_received_messages_counter(value);
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