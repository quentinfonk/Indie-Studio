/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** EntityObjects
*/

#ifndef BOMBERMAN_ENTITYOBJECTS_HPP
#define BOMBERMAN_ENTITYOBJECTS_HPP

#include "GameObject.hpp"
#include "Model.hpp"
#include "Weapon.hpp"

class EntityObjects : public GameObject {
    public:
        EntityObjects(RAYLIB::Vector2 = {0, 0}, int = -1) {};
        ~EntityObjects() = default;

        int getHealth();
        void setShield() {_shield = true;};
        void setWeaponUse(int weapon);
        void takeDamage(int damage);
        void heal() {_health = 100;};
        bool getShield();
        bool isAlive() {return this->_alive;};
        void createWeapon(std::string weapon, int nb);
        void draw();
        std::list<Bullet> &getBullet() {return this->_tmp_bullet;};
        float _rota;
        rl::Models _model;

    protected:
        int _health = 100;
        float _scale;
        bool _shield = false;
        bool _alive = true;
        int _weaponUse = 0;
        int _nbBullet = 1;
        Weapon *_weapon1;
        Weapon *_weapon2;
        std::list<Bullet> _bullet;
        std::list<Bullet> _tmp_bullet;
        std::map<int, bool> _hitten_bullet;
    };


#endif //BOMBERMAN_ENTITYOBJECTS_HPP