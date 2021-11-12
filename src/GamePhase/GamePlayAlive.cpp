/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GamePlayAlive
*/

#include "GamePlay.hpp"

bool compare(PowerUp *f, PowerUp *s)
{
    return f->getPower() == s->getPower();
}

namespace std {
    bool find(list<PowerUp*> lst, EnumPowerUp pw)
    {
        for (const auto &it : lst)
            if (it->getPower() == pw)
                return true;
        return false;
    }
};

void GamePlay::testThings()
{
    if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_0))
        _weapon = new Pistol();
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_1))
        _weapon = new Rifle();
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_2))
        _weapon = new Snip();
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_3))
        _power_up.push_back(new Dash);
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_4))
        _power_up.push_back(new Shield);
    else if (RAYLIB::IsKeyPressed(RAYLIB::KEY_KP_5))
        _power_up.push_back(new Speed);
    else if (RAYLIB::IsKeyDown(RAYLIB::KEY_F7)) {
        _player.takeDamage(100);
        _player.takeDamage(100);
    }
}

void GamePlay::reloadPower()
{
    static auto timeDash = TIMENOW;
    static bool boolDash = true;

    boolDash = std::find(_power_up, PUDash) ? true : false;
    if (!boolDash && CHRONO(timeDash) >= 4000) {
        boolDash = false;
        timeDash = TIMENOW;
        _power_up.push_back(new Dash);
    } else if (boolDash)
        timeDash = TIMENOW;
}

void GamePlay::updatePowerUp(Setting setting)
{
    _power_up.unique(compare);
    for (auto &it : _power_up)
        switch (it->getPower()) {
            case PUSpeed:
                _player.setSpeed(it->update());
                break;
            case PUShield:
                _player.setShield();
                it->use();
                break;
            case PUDash:
                if (RAYLIB::IsKeyPressed(setting.getDash())) {
                    _player.dash();
                    it->use();
                }
                break;
            case PUHealth:
                _player.heal();
                it->use();
                break;
            case PUNothing:
                break;
        }
}

void GamePlay::collisionBulletWall()
{
    bool bullet_player = true;
    float player_radius = 0.15f;
    auto playerPos = _player.getPos();
    static rl::Sound music = rl::Sound();

    for (auto &itblock : _blocks) {
        auto blockPos = itblock->getPos();
        RAYLIB::Rectangle blockPhysic = {blockPos.x, blockPos.y, 1, 1};
        bool col = RAYLIB::CheckCollisionCircleRec(playerPos, player_radius, blockPhysic);

        if (col)
            _player.setPos(_oldPlayerPos);
        //check collision bullet  /walls
        for (auto &it : _bullet) {
            if (RAYLIB::CheckCollisionCircleRec(it.getPos(), 0.05, blockPhysic)) {
                it.isReal = false;
                if (itblock->isBreakable) {
                    music.playWallBreak();
                    _blocks.remove(itblock); // remove breakable block
                    return;
                }
            }
            else if (bullet_player) {
                if (RAYLIB::CheckCollisionCircles(it.getPos(), 0.05, playerPos, player_radius)) {
                    it.isReal = false;
                    _player.takeDamage(it.getDamage());
                }
            }
        }
        bullet_player = false;
    }
}

void GamePlay::updateLocal(Setting setting)
{
    float player_radius = 0.15f;
    auto it_items = _items.begin();
    auto playerPos = _player.getPos();

    this->_player.move(setting);

    for (auto &it : _items) {
        bool col = RAYLIB::CheckCollisionCircles(it->getPos(), player_radius, playerPos, player_radius);
        if (!col) {
            it_items++;
            continue;
        }
        if (it->isWeapon) {
            _weapon = (Weapon *)it;
            it->isWear = true;
        }
        else  {
            _power_up.push_back((PowerUp *)it);
            it->isWear = true;
        }
        _items.erase(it_items);
        break;
    }
    // handle player / block colision
    collisionBulletWall();
    this->delFalseBullet();
    //end collision
    this->_player.rotate();
    ///update weapon
    _weapon->update(_player.getPos(), _player._rota);
    if (RAYLIB::IsMouseButtonDown(RAYLIB::MOUSE_LEFT_BUTTON))
        _bullet.push_back(_weapon->shoot(0));
    //update camera
        auto ppos = this->_player.getPos();
        ACTIVE_CAMERA.updateCamera(setting, {ppos.x, ppos.y});
}

void GamePlay::delFalseBullet()
{
    for (auto &it : _bullet)
        if (!it.isReal) {
            _bullet.remove(it);
            // this->delFalseBullet();
            break;
        }
}