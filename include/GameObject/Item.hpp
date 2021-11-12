/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Item
*/

#ifndef BOMBERMAN_ITEM_HPP
#define BOMBERMAN_ITEM_HPP

#include "GameObject.hpp"
#include "Encapsulation/Model.hpp"

namespace game_object {
    class Item : public GameObject {
    public:
        ~Item() = default;
        bool isWear = false;
        void draw();
        bool isWeapon = false;
    protected:
        rl::Models _model;
    };
}

#endif //BOMBERMAN_ITEM_HPP