/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Sound
*/

#include "Sound.hpp"

rl::Sound::Sound()
{
}

rl::Sound::~Sound()
{
}

void rl::Sound::playSniperShoot()
{
    static int i =0;
    if (i == 0) {
        this->_sniperShoot = RAYLIB::LoadSound("assets/sound/sniper.mp3");
        i++;
    }
    RAYLIB::PlaySoundMulti(this->_sniperShoot);
}

void rl::Sound::playEndMusic()
{
    static int i =0;
    if (i == 0) {
    this->_endMusic = RAYLIB::LoadSound("assets/sound/end_music.mp3");
        i++;
    }
    RAYLIB::PlaySoundMulti(this->_endMusic);
}

void rl::Sound::playGameMusic()
{
    static int i =0;
    if (i == 0) {
        this->_gameMusic = RAYLIB::LoadSound("assets/sound/game_music.mp3");
        i++;
    }
    RAYLIB::PlaySoundMulti(this->_gameMusic);
}

void rl::Sound::playGunShoot()
{
    static int i =0;
    if (i == 0) {
        this->_gunShoot = RAYLIB::LoadSound("assets/sound/pistolet.mp3");
        i++;
    }
    RAYLIB::PlaySoundMulti(this->_gunShoot);
}

void rl::Sound::playMenuMusic()
{
    static int i =0;
    if (i == 0) {
        this->_menuMusic = RAYLIB::LoadSound("assets/sound/pnl_uranus.mp3");
        i++;
    }
    RAYLIB::PlaySoundMulti(this->_menuMusic);
}

void rl::Sound::playRiffleShoot()
{
    static int i =0;
    if (i == 0) {
        this->_riffleShoot = RAYLIB::LoadSound("assets/sound/m4.mp3");
        i++;
    }
    RAYLIB::PlaySoundMulti(this->_riffleShoot);
}

void rl::Sound::playTakeDamage()
{
    static int i =0;
    if (i == 0) {
        this->_takeDamage = RAYLIB::LoadSound("assets/sound/damage.mp3");
        i++;
    }
    RAYLIB::PlaySoundMulti(this->_takeDamage);
}

void rl::Sound::playWallBreak()
{
    static int i =0;
    if (i == 0) {
        this->_wallBreak = RAYLIB::LoadSound("assets/sound/explosion.mp3");
        i++;
    }
    RAYLIB::PlaySoundMulti(this->_wallBreak);
}

void rl::Sound::playDead()
{
    static int i =0;
    if (i == 0) {
        this->_dead = RAYLIB::LoadSound("assets/sound/mort.mp3");
        i++;
    }
    RAYLIB::PlaySoundMulti(this->_dead);
}

void rl::Sound::stopAllMusic()
{
    RAYLIB::StopSound(this->_menuMusic);
    RAYLIB::StopSound(this->_gameMusic);
    RAYLIB::StopSound(this->_endMusic);
}