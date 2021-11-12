/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Pause
*/

#ifndef PAUSE_HPP_
#define PAUSE_HPP_

#include "Game.hpp"
#include "Player.hpp"
#include "Lobby.hpp"
#include "Ai.hpp"
#include "Map.hpp"
#include "Map3D.hpp"

class Pause {
    public:
        Pause();
        ~Pause();
        GamePhase launch();
        GamePhase restart();    
    protected:
        RAYLIB::Texture2D _tpausebackground;
        Button _bMenu;
        Button _bResume;
        Button _bQuitgame;
        Button _bSettingsgame;
        rl::Text _tMenu;
        rl::Text _tResume;
        rl::Text _tQuitgame;
        rl::Text _tSettingsgame;
};

#endif /* !PAUSE_HPP_ */
