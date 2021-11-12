/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Game
*/

#include "Game.hpp"
#include "Menu.hpp"
#include "Lobby.hpp"
#include "GamePlay.hpp"
#include "Play.hpp"
#include "Setting.hpp"
#include "Pause.hpp"
#include "End.hpp"

static int signalStatus = 0;

Game::Game()
{
}

Game::~Game()
{
}

void signal_handler(int signal)
{
    if (signal != 0)
        signalStatus = signal;
}

void Game::launch(rl::Window win)
{
    static rl::Sound music = rl::Sound();
    GamePhase statut = MenuPhase;
    GamePhase old = MenuPhase;
    std::pair<bool, Menu> menu = {false, Menu()};
    std::pair<bool, Lobby> lobby = {false, Lobby()};
    std::pair<bool, GamePlay> gameplay = {false, GamePlay()};
    std::pair<bool, Play> play = {false, Play()};
    std::pair<bool, Setting> setting = {false, Setting()};
    std::pair<bool, Pause> pause = {false, Pause()};
    std::pair<bool, End> end = {false, End()};

    #if not defined(_WIN32)
        std::signal(SIGINT, signal_handler);
    #endif
    music.playMenuMusic();
    while (statut != QuitPhase && win.loop()) {
        if (statut == RestartPhase)
            break;
        RAYLIB::BeginDrawing();
        win.clear({255, 255, 255, 255});
        if (signalStatus != 0)
            statut = QuitPhase;
        if (RAYLIB::IsKeyPressed(RAYLIB::KEY_F6)) {
            rl::Window::loading();
            statut = GamePlayPhase;
        }
        switch (statut) {
        case MenuPhase:
            if (menu.first) {
                statut = menu.second.restart();
                old = MenuPhase;
            }
            else {
                statut = menu.second.launch();
                menu.first = true;
            }
            break;
        case LobbyPhase:
            if (lobby.first)
                statut = lobby.second.restart(this->_client, menu.second.getIp(), menu.second.getPort(), setting.second);
            else {
                statut = lobby.second.launch(this->_client, menu.second.getIp(), menu.second.getPort(), setting.second);
                lobby.first = true;
            }
            break;
        case GamePlayPhase:
            if (gameplay.first)
                statut = gameplay.second.restart(setting.second);
            else {
                statut = gameplay.second.launch(setting.second);
                gameplay.first = true;
            }
            break;
        case PlayPhase:
            if (play.first)
                statut = play.second.restart(this->_client, setting.second);
            else {
                statut = play.second.launch(this->_client, lobby.second, setting.second);
                play.first = true;
            }
            break;
        case PausePhase:
            if (pause.first) {
                statut = pause.second.restart();
                old = PausePhase;
            }
            else {
                statut = pause.second.launch();
                pause.first = true;
                old = PausePhase;
            }
            break;
        case EndPhase:
            if (end.first)
                statut = end.second.restart();
            else {
                statut = end.second.launch();
                end.first = true;
            }
            break;
        case SettingPhase:
            if (setting.first)
                statut = setting.second.restart(old);
            else {
                printf("old = %d\n", old);
                statut = setting.second.launch(old);
                setting.first = true;
            }
            break;
        default:
            break;
        }
        RAYLIB::EndDrawing();
    }
    if (lobby.second.isHost())
        this->_client->send(CLOSING_SERVER);
    else if (lobby.second.getMe() != -1)
        this->_client->send(CLIENT_CLOSING_CONNECTION);
    #if defined (DEBUG)
        std::cout << "Quiting" << std::endl;
    #endif
    if (statut == RestartPhase)
        this->launch(win);
}