/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Lobby
*/

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

#include "Button.hpp"
#include "InputButton.hpp"
#include "Game.hpp"
#include "encapsulation.hpp"
#include "Player.hpp"
#include "Client.hpp"
#include <map>
#include <memory>
#include <chrono>
#include <thread>

class Lobby {
    enum Phase {
        MainPhase,
        JoinPhase
    };
    public:
        Lobby();
        ~Lobby();
        GamePhase launch(Client *&, std::string, std::string, Setting);
        GamePhase restart(Client *&, std::string, std::string, Setting);
        GamePhase mainPhase(GamePhase, Client *&, Setting);
        GamePhase joinPhase(GamePhase, Client *&, std::string, std::string);

        int getMe(void);
        bool isHost(void);
        int getReadyPlayer(void);
        int getPlayer(void);
        std::map<int, GameObject *> getObj(void);
        void setReadyPlayer(int);
        void setPlayer(int);

    protected:
    private:
        Phase _phase;
        std::map<int, GameObject *> _obj;
        std::list<BlockObject *> _blocks;
        int _player;
        int _readyPlayer;
        Client *_client;
        size_t _me;
        rl::Camera _TopCamera;
        int _renderDistance = 40;
        bool _host;
        bool _ready;
        std::string _port;
        std::string _localIp;
        std::string _publicIp;
        
        Button _bReady;
        rl::Text _tReady;
        rl::Text _tIps;
};

#endif /* !LOBBY_HPP_ */