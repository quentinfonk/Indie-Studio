/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#define timeNow std::chrono::high_resolution_clock::now()
#define Chrono(x) std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - x).count()

#include "GamePhase.hpp"
#include "Menu.hpp"
#include "encapsulation.hpp"
#include "Client.hpp"
#include "Server.hpp"

// #define DEBUG

class Game {
    public:
        Game();
        ~Game();
        void launch(rl::Window);

    protected:
    private:
        Client *_client;
        Server *_server;
};

#endif /* !GAME_HPP_ */
