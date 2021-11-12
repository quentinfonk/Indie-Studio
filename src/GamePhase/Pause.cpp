/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Pause
*/

#include "Pause.hpp"
#include "Menu.hpp"
#include "Server.hpp"
#include "Game.hpp"
#include "Pause.hpp"

Pause::Pause()
{
}

Pause::~Pause()
{
}

GamePhase Pause::launch()
{
    this->_tpausebackground = RAYLIB::LoadTexture("assets/texture/pausebackground.png");
    this->_bMenu = Button("assets/texture/button.png", 20, 20, 21.4, 10);
    this->_bSettingsgame = Button("assets/texture/button.png", 60, 20, 21.4, 10);
    this->_bQuitgame = Button("assets/texture/button.png", 20, 60, 21.4, 10);
    this->_bResume = Button("assets/texture/button.png", 60, 60, 21.4, 10);
    this->_tMenu = rl::Text("Menu", 26, 22, 37, RAYLIB::BLACK);
    this->_tSettingsgame = rl::Text("Settings", 63, 22, 37, RAYLIB::BLACK);
    this->_tResume = rl::Text("Resume", 64, 62, 37, RAYLIB::BLACK);
    this->_tQuitgame = rl::Text("Quit", 26, 62, 37, RAYLIB::BLACK);
    return (this->restart());
}

GamePhase Pause::restart()
{
    GamePhase gamePhase = PausePhase;
    
    if (this->_bMenu.isClicked())
        gamePhase = MenuPhase;
    if (this->_bSettingsgame.isClicked())
        gamePhase = SettingPhase;
    if (this->_bQuitgame.isClicked())
        return (QuitPhase);
    if (this->_bResume.isClicked()) {
        gamePhase = GamePlayPhase;
    }
    RAYLIB::DrawTextureEx(this->_tpausebackground, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_bQuitgame.draw();
    this->_bResume.draw();
    this->_bSettingsgame.draw();
    this->_bMenu.draw();
    this->_tQuitgame.draw();
    this->_tResume.draw();
    this->_tSettingsgame.draw();
    this->_tMenu.draw();
    return (gamePhase);
}
