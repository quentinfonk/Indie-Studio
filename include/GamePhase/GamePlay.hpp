/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GamePlay
*/

#ifndef GAMEPLAY_HPP_
#define GAMEPLAY_HPP_

#include <list>
#include <vector>

#include "GamePhase.hpp"
#include "BlockObject.hpp"
#include "EntityObjects.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include "Map3D.hpp"
#include "Player.hpp"
#include "Encapsulation/Camera.hpp"
#include "Encapsulation/Gamepad.hpp"
#include "Encapsulation/Window.hpp"
#include "Encapsulation/Text.hpp"
#include "Weapon.hpp"
#include "PowerUp.hpp"
#include "Sound.hpp"
#include "Setting.hpp"

#define ACTIVE_CAMERA ((!this->_player.isAlive()) ? this->_FPCamera : this->_TopCamera)

#define GROUNDCOLOR {119,136,153, 255}
#define SPAWNCOLOR {233,150,122, 255}
#define ITEMCOLOR {42, 157, 244, 255}

class GamePlay{
    enum EnumItems {
    ITSpeed = 0,
    ITHealth,
    ITShield,
    ITRifle,
    ITSnip
    };
    public:
        const std::map<EnumItems, game_object::Item*> enumToItem = {
            {ITSpeed, (game_object::Item*) new Speed},
            {ITHealth, (game_object::Item*) new Health},
            {ITShield, (game_object::Item*) new Shield},
            {ITRifle, (game_object::Item*) new Rifle},
            {ITSnip, (game_object::Item*)new  Snip}
        };
        GamePlay();
        ~GamePlay() = default;

        GamePhase launch(Setting);
        GamePhase restart(Setting);

    private: //methodes
        //set
        void placeItems(std::list<std::pair<float, float>> poslist);
        void setBlocks(std::list<BlockObject*> obj) {_blocks = obj;};
        void setEnemies(std::list<EntityObjects*> obj) {_enemies = obj;};
        void setItems(std::list<game_object::Item*> obj) {_items = obj;};
        void nonToPoi(std::list<MapBlock>);
        void collisionBulletWall();
        void lifeAndShield();
        //alive methode
        void updateLocal(Setting);
        void updatePowerUp(Setting);
        void testThings();
        void delFalseBullet();
        void reloadPower();

        //spec method
        //todo

        //other methods
        void aliveCall(Setting);
        void specCall(Setting);
        void drawAll();

    private: //attr
        Player _player;
        RAYLIB::Vector2 _oldPlayerPos;
        std::list<BlockObject*> _blocks;
        std::list<EntityObjects*> _enemies;
        std::list<game_object::Item*> _items;
        std::list<Bullet> _bullet;
        int _renderDistance = 40;
        Weapon *_weapon;
        std::list<PowerUp*> _power_up;
        //server
        rl::Camera _FPCamera;
        rl::Camera _TopCamera;
        Gamepad _gmp = Gamepad(0);
        bool _isFpCam = true;
        std::pair<float, float> _mapSize;
        std::pair<float, float> _spawn;
        std::list<std::pair<float, float>> _spawns;
        RAYLIB::Texture2D _heart;
        RAYLIB::Texture2D _shield;
};

#endif /* !GAMEPLAY_HPP_ */
