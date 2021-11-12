/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** main
*/

// #include <iostream>

#include "encapsulation.hpp"
#include "Game.hpp"
#include "Server.hpp"

static const int WIN_HEIGHT = RAYLIB::GetScreenHeight();
static const int WIN_WIDTH = RAYLIB::GetScreenWidth();

void launchServer(int port)
{
    if (port < 2000 || port > 65535) {
        std::cout << "Server failed: port is invalid" << std::endl;
        return;
    }
    std::cout << "Launching server..." << std::endl;
    boost::asio::io_service io_service;
    udp::resolver resolver(io_service);
    Server server(io_service, port);
    std::cout << "Server is up and running at port " << std::to_string(port) << std::endl;
    std::cout << "You can close this whenever you don't need the server anymore." << std::endl;
    io_service.run();
    std::cout << "Ending server..." << std::endl;
}

int main(int ac, char **av)
{
    try {
        int WIN_HEIGHT = RAYLIB::GetScreenHeight();
        int WIN_WIDTH = RAYLIB::GetScreenWidth();

        if (ac == 3 && std::string(av[1]) == "--server") {
            launchServer(std::atoi(av[2]));
            return (0);
        }
        rl::Window win(WIN_WIDTH, WIN_HEIGHT, "Indie Studio");
        win.fullscreen();
        rl::Window::loading();
        RAYLIB::InitAudioDevice();
        Game game;

        game.launch(win);
        win.destroy();
        return 0;
    }
    catch (...) {
        std::cout << "Oops ! Something went wrong..." << std::endl;
        return 84;
    }
}