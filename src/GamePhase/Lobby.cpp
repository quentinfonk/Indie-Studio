/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Lobby
*/

#include "Lobby.hpp"
#include <string>
#include "Server.hpp"
#include "Encapsulation/Text.hpp"
#include <stdio.h>
#include <stdlib.h>
#if defined(_WIN32)
    #include <windows.h>
    #include <winsock.h>
#else
    #include <stdlib.h>
#endif

Lobby::Lobby()
{
    this->_me = -1;
    this->_TopCamera = rl::Camera({0, 6, 0});
    this->_player = 1;
    this->_readyPlayer = 0;
    this->_host = false;
    this->_ready = false;
}

Lobby::~Lobby()
{
}

bool Lobby::isHost(void)
{
    return (this->_host);
}

int Lobby::getMe(void)
{
    return (this->_me);
}

int Lobby::getReadyPlayer(void)
{
    return (this->_readyPlayer);
}

void Lobby::setReadyPlayer(int readyPlayer)
{
    this->_readyPlayer = readyPlayer;
}

int Lobby::getPlayer()
{
    return (this->_player);
}

void Lobby::setPlayer(int player)
{
    this->_player = player;
}

std::map<int, GameObject *> Lobby::getObj()
{
    return (this->_obj);
}

GamePhase Lobby::launch(Client *&client, std::string ip, std::string port, Setting setting)
{
    this->_phase = JoinPhase;

    this->_bReady = Button("assets/texture/button.png", 70, 85, 21.4, 10);
    this->_tReady = rl::Text("Ready  " + std::to_string(this->_readyPlayer) + "/" + std::to_string(this->_player), 72, 88, 30, RAYLIB::BLACK);
    this->_tIps = rl::Text("", 1, 2, 20, RAYLIB::LIGHTGRAY);

    return (this->restart(client, ip, port, setting));
}

GamePhase Lobby::restart(Client *&client, std::string ip, std::string port, Setting setting)
{
    GamePhase gamePhase = LobbyPhase;

    switch (this->_phase) {
    case Lobby::MainPhase:
        gamePhase = this->mainPhase(gamePhase, client, setting);
        break;
    case Lobby::JoinPhase:
        gamePhase = this->joinPhase(gamePhase, client, ip, port);
        break;

    default:
        break;
    }
    return (gamePhase);
}

GamePhase Lobby::mainPhase(GamePhase gamePhase, Client *&client, Setting setting)
{
    GameObject::gestData(this->_obj, this->_client->read(), this->_client, *this);
    ((Player *)this->_obj[this->_me])->gest(client, this->_blocks, setting);
    // rl::Text(std::to_string(((Player *)this->_obj[this->_me])->_rota), 10, 10, 15, {255, 0, 0, 255}).draw();
    if (!this->_ready && this->_bReady.isClicked()) {
        this->_ready = true;
        client->send("READY;\n");
    }
    if (this->_readyPlayer == this->_player) {
        rl::Window::loading();
        return(PlayPhase);
    }
    this->_tReady.setText("Ready  " + std::to_string(this->_readyPlayer) + "/" + std::to_string(this->_player));

    // 3D Drawing
    RAYLIB::BeginMode3D(this->_TopCamera.getCamera());
    RAYLIB::Vector2 pos = ((Player *)this->_obj[this->_me])->getPos();
    _TopCamera.updateCamera(setting, {pos.x, pos.y});
    for (auto it = this->_obj.begin(); it != this->_obj.end() ; it++) {
        it->second->draw();
    }
    RAYLIB::DrawGrid(1000, 10);
    RAYLIB::DrawPlane({500, -0.01, 500}, { 500, 500}, {119,136,153, 255}); //draw flor
    RAYLIB::EndMode3D();

        // 2D Drawing
    this->_bReady.draw();
    this->_tReady.draw();
    this->_tIps.draw();

    return (gamePhase);
}

GamePhase Lobby::joinPhase(GamePhase gamePhase, Client *&client, std::string ip, std::string port)
{
    rl::Window::loading();
    std::cout << "Connecting to Ip: " << ip << " / Port: " << port << std::endl;

    // Connect to server
    #if defined(_WIN32)
        Sleep(1000);
    #else
        sleep(1);
    #endif
    try {
        client = new Client(ip, std::atoi(port.c_str()));
    }
    catch (std::exception &e) {
        return (MenuPhase);
    }
    this->_client = client;
    this->_client->launch();
    this->_client->send(INCOMMING_CONNECTION);
    #if defined(_WIN32)
        Sleep(3000);
    #else
        sleep(1);
    #endif
    std::string str = client->read();
    if (str == "") { // GESTION ERREUR
        std::cerr << "First connexion time out" << std::endl;
        return (LobbyPhase);
    }
    GameObject::gestData(this->_obj, str, client, *this);

    // Get server data
    #if defined(DEBUG)
        std::cout << "Get Info Start" << std::endl;
    #endif
    #if defined(_WIN32)
        Sleep(1000);
    #else
        sleep(1);
    #endif
    str = client->read();
    GameObject::gestData(this->_obj, str, client, *this);
    #if defined(DEBUG)
        std::cout << "Get Info End" << std::endl;
    #endif
    this->_me = this->_obj.size();
    if (this->_me == 0)
        this->_host = true;
    this->_player += this->_me;

    // Send server data
    client->send("PLAYER;ID:" + std::to_string(this->_me) + ";X:500;Y:500;\n");
    #if defined(_WIN32)
        Sleep(1000);
    #else
        sleep(1);
    #endif
    str = client->read();
    if (str == "") { // GESTION ERREUR
        std::cerr << "Getting info time out" << std::endl;
        return (LobbyPhase);
    }
    GameObject::gestData(this->_obj, str, client, *this);

    // Get Ip
    FILE *file;
    char bufLocal[128];
    char bufPublic[128];
    std::string line;
    std::string ips = "These infos has been copied to your clipboard\n";
    #if defined(_WIN32)
        file = _popen("curl ifconfig.me", "r");
    #else
        file = popen("curl ifconfig.me", "r");
    #endif
    while(fgets(bufPublic, 128, file))
        this->_publicIp += bufPublic;
    #if defined(_WIN32)
        WSAData wsaData;
        WSAStartup(MAKEWORD(1, 1), &wsaData);
        char ac[80];
        gethostname(ac, sizeof(ac));
        struct hostent *phe = gethostbyname(ac);
        for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
            struct in_addr addr;
            memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
            this->_localIp += inet_ntoa(addr);
        }
        WSACleanup();
    #else
        file = popen("hostname -I | awk '{print $1}'", "r");
        while(fgets(bufLocal, 128, file))
            this->_localIp += bufLocal;
    #endif
    this->_port = port;

    ips += "Public Ip: " + this->_publicIp + "\n";
    ips += "Local Ip: " + this->_localIp + "\n";
    ips += "Port: " + this->_port;
    this->_tIps.setText(ips);
    ips.erase(0, 46);
    RAYLIB::SetClipboardText(ips.c_str());

    this->_phase = MainPhase;
    return (gamePhase);
}