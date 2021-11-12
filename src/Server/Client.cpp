/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Client
*/

#include "Client.hpp"
#include "Message.hpp"
#include "Game.hpp"

Client::Client(std::string host, int port) : _socket(this->_io_service, udp::endpoint(udp::v4(), 0))
{
    udp::resolver resolver(this->_io_service);
    udp::resolver::query query(udp::v4(), host, std::to_string(port));
    this->_remote_endpoint = *(resolver.resolve(query));
    this->startReceive();
}

std::string Client::read(void)
{
    std::string str(this->_all_recv);

    this->_all_recv.erase(0, str.size());
    #if defined(DEBUG)
    if (str != "")
        std::cout << "Client: " << str << std::endl;
    #endif
    return (str);
}

void Client::send(std::string str)
{
    this->_socket.send_to(boost::asio::buffer(str), this->_remote_endpoint);
}

void Client::startReceive(void)
{
    this->_socket.async_receive_from(
        boost::asio::buffer(this->_recv_buffer),
        this->_remote_endpoint,
        boost::bind(
            &Client::handleReceive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Client::handleReceive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::string str_received = std::string(reinterpret_cast<const char*>(this->_recv_buffer.data()), bytes_transferred);
        this->_all_recv.append(str_received);
    }
    this->startReceive();
}

std::string Client::getReponse(void)
{
    std::string str;
    auto time = timeNow;

    while(Chrono(time) <= 5000) {
        str = this->read();
        if (str != "")
            return (str);
    }
    return (TIMEOUT_CONNECTION);
}

void Client::launch(void)
{
    try {
        boost::thread run_thread(boost::bind(&boost::asio::io_service::run, boost::ref(this->_io_service)));
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}