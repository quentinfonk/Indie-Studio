/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Play
*/

#ifndef PLAY_HPP_
#define PLAY_HPP_

#include "Game.hpp"
#include "Player.hpp"
#include "Lobby.hpp"
#include "Ai.hpp"
#include "Map.hpp"
#include "Map3D.hpp"
#include "PowerUp.hpp"

#define ACTIVE_CAM(x) ((!x) ? this->_FPCamera : this->_TopCamera)

#define GROUNDCOLOR {119,136,153, 255}
#define SPAWNCOLOR {233,150,122, 255}
#define ITEMCOLOR {42, 157, 244, 255}

class Play {
    enum Phase {
        MainPhase,
        JoinPhase
    };
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
        Play();
        ~Play();
        GamePhase launch(Client *&, Lobby &, Setting);
        GamePhase restart(Client *&, Setting);
        GamePhase mainPhase(GamePhase, Client *&, Setting);
        GamePhase joinPhase(GamePhase, Client *&);
        void placeItems(std::list<std::pair<float, float>>);
        void lifeAndShield();
        void reloadPower();
        void updatePowerUp(Setting);
        static bool compare(PowerUp *f, PowerUp *s);

    protected:
    private:
        Phase _phase;
        std::map<int, GameObject *> _obj;
        int _player;
        bool _host;
        size_t _me;
        rl::Camera _TopCamera;
        rl::Camera _FPCamera;
        int _renderDistance = 40;
        std::vector<Ai *> _ai;
        int _nbAi;
        int _dead = 0;
        std::vector<std::vector<char>> _map;
        std::pair<float, float> _mapSize;
        std::list<BlockObject *> _blocks;
        std::list<std::pair<float, float>> _spawns;
        std::list<game_object::Item*> _items;
        std::list<PowerUp*> _power_up;

        rl::Text _tHp;
        RAYLIB::Texture2D _heart;
        RAYLIB::Texture2D _shield;
};

#endif /* !PLAY_HPP_ */
