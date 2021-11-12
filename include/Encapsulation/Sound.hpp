/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "include.hpp"


namespace rl {
    class Sound
    {
        public:
            Sound();
            ~Sound();
            void playSniperShoot();
            void playGunShoot();
            void playRiffleShoot();
            void playWallBreak();
            void playTakeDamage();
            void playMenuMusic();
            void playGameMusic();
            void playEndMusic();
            void playDead();
            void stopAllMusic();
        private:
            RAYLIB::Sound _sniperShoot;
            RAYLIB::Sound _gunShoot;
            RAYLIB::Sound _riffleShoot;
            RAYLIB::Sound _wallBreak;
            RAYLIB::Sound _takeDamage;
            RAYLIB::Sound _menuMusic;
            RAYLIB::Sound _gameMusic;
            RAYLIB::Sound _endMusic;
            RAYLIB::Sound _dead;
    };
}
#endif /* !SOUND_HPP_ */
