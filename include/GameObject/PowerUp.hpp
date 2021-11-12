/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** PowerUp
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#define TIMENOW std::chrono::high_resolution_clock::now()
#define CHRONO(x) std::chrono::duration_cast<std::chrono::milliseconds>(TIMENOW - x).count()

#include <map>

#include "Item.hpp"

enum EnumPowerUp {
    PUNothing = 0,
    PUSpeed,
    PUShield,
    PUDash,
    PUHealth
};

class PowerUp : public game_object::Item 
{
    public:
        const rl::Models speedModel = rl::Models("assets/powerUp/chilli/chilli.glb");
        const rl::Models shieldModel = rl::Models("assets/powerUp/shield/shield.glb");
        const rl::Models dashModel = rl::Models("assets/weapons/Baretta/Beretta.obj");
        const rl::Models healthModel = rl::Models("assets/powerUp/Heart/heart.obj");

        const std::map<EnumPowerUp, rl::Models> powerUpModel = {
            {PUSpeed, speedModel},
            {PUShield, shieldModel},
            {PUDash, dashModel},
            {PUHealth, healthModel}
        };
        ~PowerUp() = default;
        void use() {_type = PUNothing;};
        bool update() {
            static auto start = TIMENOW;
            if (CHRONO(start) >= this->_time * 1000) {
                this->_type = PUNothing;
                return false;
            }
            return true;
        };
        void setModel() {
            try {
                _model = powerUpModel.at(_type);
            } catch(...){};
        };
        EnumPowerUp getPower() const {return _type;};
        std::string serialize() {return std::string("");};
        void deserialize(std::string) {};

    protected:
        EnumPowerUp _type;
        unsigned short _time;
};

class Speed : public PowerUp
{
    public:
        Speed() {_type = PUSpeed; _time = 15; setModel(); this->_objType = "Speed";};
        ~Speed() = default;
};

class Shield : public PowerUp
{
    public:
        Shield() {_type = PUShield; _time = 0; setModel(); this->_objType = "Shield";};
        ~Shield() = default;
};

class Dash : public PowerUp
{
    public:
        Dash() {_type = PUDash; _time = 0; setModel(); this->_objType = "Dash";};
        ~Dash() = default;
};

class Health : public PowerUp
{
    public:
        Health() {_type = PUHealth; _time = 0; setModel(); this->_objType = "Health";};
        ~Health() = default;
};

#endif /* !POWERUP_HPP_ */
