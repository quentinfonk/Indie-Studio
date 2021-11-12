/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Server
*/

#include "Message.hpp"
#include "Server.hpp"
#include "Game.hpp"

Server::Server(boost::asio::io_service &io_service, int port) : _socket(io_service, udp::endpoint(udp::v4(), port))
{
    this->startReceive();
}

bool Server::isConnectionNew(udp::endpoint endpoint)
{
    for (auto it : this->_connection_pool)
        if (it == endpoint)
            return false;
    return true;
}

void Server::startReceive(void)
{
    this->_socket.async_receive_from(
        boost::asio::buffer(this->_recv_buf),
        this->_last_endpoint,
        boost::bind(
            &Server::handleReceive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Server::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        if (this->isConnectionNew(this->_last_endpoint))
            this->_connection_pool.push_back(this->_last_endpoint);
        std::string line(this->_recv_buf.begin(), bytes_transferred);
        this->handleCommand(line);
        // boost::thread run_thread(&Server::handleCommand, line);
        // boost::thread thr(&Server::handleCommand, &line);
        
        // std::thread thr(&Server::handleCommand, std::ref(line));
        // thr.detach();
    }
    this->startReceive();
}

void Server::sendToAll(std::string str)
{
    boost::shared_ptr<std::string> message(new std::string(str));

    #if defined(DEBUG)
        std::cout << "Sending to all: " << str << std::endl;
    #endif
    for (auto it : this->_connection_pool)
        this->_socket.send_to(boost::asio::buffer(*message), it);
}

void Server::sendToSender(std::string str)
{
    boost::shared_ptr<std::string> message(new std::string(str));

    this->_socket.send_to(boost::asio::buffer(*message), this->_last_endpoint);
}

void Server::sendTo(SEND send, std::string message)
{
    if (send == ALL)
        this->sendToAll(message);
    else if (send == SENDER)
        this->sendToSender(message);
    return;
}

void Server::handleCommand(std::string line)
{
    if (line == CLOSING_SERVER) {
        sendTo(ALL, CLOSING_CONNECTION);
        std::exit(0);
    }
    else
        sendTo(ALL, line);
}

void Server::launch(int port)
{
    try {
        #if defined(_WIN32)
            system((std::string("start cmd /c bomberman --server ") + std::to_string(port)).c_str());
        #else
            system((std::string("gnome-terminal -e \"./bomberman --server ") + std::to_string(port) + std::string("\"")).c_str());
        #endif
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}















































































































// #include "Server.hpp"
// #if defined(_WIN32)
//     #include <windows.h>
// #endif

// Server::Server(boost::asio::io_service& io_service, int port) : _socket(io_service, udp::endpoint(udp::v4(), port)), _port(port)
// {
//     startReceive();
// }

// bool Server::isConnectionNew(udp::endpoint endpoint)
// {
//     for (auto it : this->_connection_pool)
//         if (it.second == endpoint)
//             return false;
//     return true;
// }

// void Server::startReceive(void)
// {
//     this->_socket.async_receive_from(
//         boost::asio::buffer(_recv_buffer),
//         this->_new_endpoint,
//         boost::bind(
//             &Server::handleReceive,
//             this,
//             boost::asio::placeholders::error,
//             boost::asio::placeholders::bytes_transferred
//         )
//     );
// }

// std::string Server::getUUIDFromString(std::string line)
// {
//     std::string uuid;
//     size_t pos = line.find("UUID:");

//     if (pos == std::string::npos)
//         return ("");
//     pos += 5;
//     for (size_t i = pos; line[i] != '\0' && line[i] != ';'; i += 1)
//         uuid += line[i];
//     return uuid;
// }

// void Server::sendToAll(std::string str)
// {
//     boost::shared_ptr<std::string> message(new std::string(str));

//     for (auto it : this->_connection_pool)
//         this->_socket.send_to(boost::asio::buffer(*message), it.second);
// }

// void Server::sendToSender(std::string str)
// {
//     boost::shared_ptr<std::string> message(new std::string(str));

//     this->_socket.send_to(boost::asio::buffer(*message), this->_new_endpoint);
// }

// void Server::sendTo(SEND send, std::string message)
// {
//     if (send == ALL) {
//         this->sendToAll(message);
//         std::cout << "Send to all : " << message << std::endl;
//         // std::thread{Server::sendToAll, std::ref(message)}.detach();
//     }
//     else if (send == SENDER) {
//         this->sendToSender(message);
//         // std::thread{Server::sendToSender, std::ref(message)}.detach();
//     }
//     return;
// }

// void Server::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
// {
//     if (!error || error == boost::asio::error::message_size) {
//         std::string line(this->_recv_buffer.begin(), bytes_transferred);
//         std::cout << "JHGFDFGHJ" << std::endl;
//         std::cout << "Server recieve: " << line << std::endl;
//         std::string uuid = getUUIDFromString(line);
//         if (this->_connection_pool.find(uuid) == this->_connection_pool.end()) // If client uuid doesn't exist in connectio pool yet, add it.
//             this->_connection_pool[uuid] = this->_new_endpoint;
//         if (line.find(INCOMMING_CONNECTION) != std::string::npos)
//             sendTo(ALL, ACCEPTED_CONNECTION);
//         else {
//             // UUID:YUAZUIEIUHIOAEHOIEH;truc a ecrire
//             size_t pos = line.find_first_of(";");
//             if (pos == std::string::npos)
//                 std::cout << "What the hell is that: \"" << line << "\"" << std::endl;
//             else
//                 sendTo(ALL, line.substr(pos + 1));
//         }
//     }
//     this->startReceive();
// }

// #if defined(_WIN32)
//     DWORD WINAPI mythread(LPVOID lpParameter)
//     {
//         boost::asio::io_service& io_service = *((boost::asio::io_service*)lpParameter);
//         io_service.run();
//         return 0;
//     }
// #endif

// bool Server::launchServer(boost::asio::io_service& io_service)
// {
//     #if defined(_WIN32)
//         DWORD myThreadID;
//         HANDLE myHandle = CreateThread(0, 0, mythread, &io_service, 0, &myThreadID);
//         return (true);
//     #else
//         switch (fork()) {
//             case (-1):
//                 return (false);
//             case (0):
//                 std::cout << "Server Start at port: " << std::to_string(this->_port) << std::endl;
//                 io_service.run();
//                 std::cout << "Stoping server ?!?!? tu fait quoi la????" << std::endl;
//                 exit(0);
//             default:
//                 return (true);
//         }
//     #endif
// }

// // int main(int ac, char **av)
// // {
// //     boost::asio::io_service io_service;
// //     Server server(io_service, atoi(av[1]));

// //     server.launchServer(io_service);
// //     while (true) { // TEST -- Occupe le prog pendant que le serv tourne
// //         std::cout << "je tourne dans le vide" << std::endl;
// //     }
// // }