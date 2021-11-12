/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "EntityObjects.hpp"
#include "Model.hpp"
#include "BlockObject.hpp"
#include "Setting.hpp"

class Player : public EntityObjects {
    public:
        Player(RAYLIB::Vector2 = {0, 0}, int = -1, bool = false);
        ~Player() = default;
        void move(Setting);
        void rotate();
        void gest(Client *&client, std::list<BlockObject *> &blocks, Setting);
        std::string serialize();
        void deserialize(std::string);
        void dash();
        void setSpeed(bool val) {_moreSpeed = val;};
        void gestColision(std::list<BlockObject *> &blocks, RAYLIB::Vector2 oldPlayerPos);

    protected:
    private:
        bool _me;
        bool _moreSpeed = false;
        // RAYLIB::Vector2 _pos;
        // float _ypos = 0;
        // float _scale;
};

#endif /* !PLAYER_HPP_ */
