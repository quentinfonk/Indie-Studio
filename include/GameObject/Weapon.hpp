/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Weapon
*/

#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include "Item.hpp"
#include "include.hpp"
#include "Model.hpp"
#include "Encapsulation/Text.hpp"
#include <chrono>
#include "Sound.hpp"

#define TIMENOW std::chrono::high_resolution_clock::now()
#define CHRONO(x) std::chrono::duration_cast<std::chrono::milliseconds>(TIMENOW - x).count()

// static auto bulletModel = rl::Models("assets/weapons/Bullet/Bullet.obj");

class Bullet : public game_object::Item
{
    public :
        Bullet(int id, RAYLIB::Vector3 pos, float rota, float cone, float damage, float speed);
        Bullet();
        ~Bullet() = default;

        void update(float radius = std::nanf("0"));
        void draw();
        RAYLIB::Model &getModel() {return (this->_model.getModel());};
        int getDamage(){return _damage;};

        std::string serialize();
        void deserialize(std::string);

        bool isReal = true;
    private :
        float _rota;
        int _damage;
        float _speed;
        rl::Models _model;
};

bool operator==(Bullet f, Bullet s);

class Weapon : public game_object::Item
{
    public:
        Weapon() {isWeapon = true;};
        ~Weapon() = default;

    // //viruital
    //     virtual void draw() = 0;

    //physical (like dl)
        Bullet shoot(int id_bullet);
        void take() {_wear = true;};
        void drop() {_wear = false;};
        void update(RAYLIB::Vector2 pos, float rota);
        std::string serialize();
        void deserialize(std::string);
        void draw();

    protected:
        unsigned short _nbBullet;
        float _cone;
        float _damage;
        float _time_shoot;
        float _bullet_speed;
        std::string _type;
        float _rota;
        bool _wear = true;
};

class Pistol : public Weapon
{
    public :
        Pistol(int id = -1, RAYLIB::Vector2 pos = {0, 0});
        ~Pistol() = default;
};

class Rifle : public Weapon
{
    public :
        Rifle(int id = -1, RAYLIB::Vector2 pos = {0, 0});
        ~Rifle() = default;
};

class Snip : public Weapon
{
    public :
        Snip(int id = -1, RAYLIB::Vector2 pos = {0, 0});
        ~Snip() = default;
};

std::pair<float, float> pointInACircle(float angle, float radius);

#endif /* !WEAPON_HPP_ */