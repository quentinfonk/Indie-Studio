/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Player
*/

#include "Player.hpp"
#include <string>
#include <Weapon.hpp>

float Vector2Angle(RAYLIB::Vector2 v1, RAYLIB::Vector2 v2)
{
    float result = atan2f(v2.y - v1.y, v2.x - v1.x)*(180.0f/PI);
    if (result < 0) result += 360.0f;
    return result;
}

Player::Player(RAYLIB::Vector2 pos, int id, bool me) : _me(me)
{
    static auto globalPlayerModel = rl::Models("assets/character/character.obj");
    static auto __bb = RAYLIB::MeshBoundingBox(globalPlayerModel._model.meshes[0]);
    static float __varForCalculateScale = __bb.min.z - __bb.max.z;
    _scale = std::abs(0.3 / __varForCalculateScale);
    this->setPos(pos);
    _model = globalPlayerModel;

    this->_rota = 0;
    this->_change = false;
    this->_id = id;
    this->_objType = "Player";
}

void Player::move(Setting setting)
{
    if (!RAYLIB::IsKeyDown(setting.getForward()) && !RAYLIB::IsKeyDown(setting.getBackward()) &&
    !RAYLIB::IsKeyDown(setting.getRight()) && !RAYLIB::IsKeyDown(setting.getLeft()))
        return;

    std::pair<float, float> move(0, 0);
    RAYLIB::Vector2 pos = this->getPos();

    float speed = (_moreSpeed ? 10 : 5);
    if (move == std::make_pair(0.0f, 0.0f)) {
        move.first += RAYLIB::IsKeyDown(setting.getForward()) - RAYLIB::IsKeyDown(setting.getBackward());
        move.second += RAYLIB::IsKeyDown(setting.getRight()) - RAYLIB::IsKeyDown(setting.getLeft());
        move.first *= RAYLIB::GetFrameTime();
        move.second *= RAYLIB::GetFrameTime();
    }
    RAYLIB::Vector2 toSet = {pos.x + move.first * speed, pos.y + move.second * speed };
    this->_pos = toSet;
    this->_change = true;
}

void Player::dash()
{
    std::pair<float, float> circlePos = pointInACircle(std::abs(_rota + 90), 1);
    this->_pos.x += circlePos.first;
    this->_pos.y += circlePos.second;
}

void Player::rotate()
{
    float newRota = -Vector2Angle({(float)RAYLIB::GetScreenWidth() / 2, (float)RAYLIB::GetScreenHeight() / 2}, RAYLIB::GetMousePosition());

    if (this->_rota == newRota)
        return;
    this->_rota = newRota;
    this->_change = true;
}

void Player::gestColision(std::list<BlockObject *> &blocks, RAYLIB::Vector2 oldPlayerPos)
{
    bool bullet_player = true;

    for (auto itBlock : blocks) {
        // With Player
        RAYLIB::Vector2 playerPos = this->_pos;
        float player_radius = 0.15f;
        RAYLIB::Vector2 blockPos = itBlock->getPos();
        RAYLIB::Rectangle blockPhysic = {blockPos.x, blockPos.y, 1, 1};
        bool col = RAYLIB::CheckCollisionCircleRec(playerPos, player_radius, blockPhysic);

        if (col)
            this->_pos = oldPlayerPos;

        // With Bullets
        for (auto &it : _bullet) {
            if (RAYLIB::CheckCollisionCircleRec(it.getPos(), 0.05, blockPhysic)) {
                it.isReal = false;
                if (itBlock->isBreakable) {
                    blocks.remove(itBlock); // remove breakable block
                    return;
                }

            }
        }
        for (auto &it : _tmp_bullet) {
            if (RAYLIB::CheckCollisionCircleRec(it.getPos(), 0.05, blockPhysic)) {
                it.isReal = false;
                if (itBlock->isBreakable) {
                    blocks.remove(itBlock); // remove breakable block
                    return;
                }

            } else if (bullet_player) {
                if (RAYLIB::CheckCollisionCircles(it.getPos(), 0.05, playerPos, player_radius) && this->_hitten_bullet.find(it.getId()) == this->_hitten_bullet.end()) {
                    it.isReal = false;
                    this->takeDamage(it.getDamage());
                    this->_hitten_bullet[it.getId()] = true;
                }
            }
        }
        bullet_player = false;
    }
    for (auto &it : _bullet) {
        if (!it.isReal) {
            _bullet.remove(it);
            break;
        }
    }
}

std::string Player::serialize()
{
    std::string str;

    // Weapon
    if (this->_weaponUse == 1)
        str += this->_weapon1->serialize();
    else if (this->_weaponUse == 2)
        str += this->_weapon2->serialize();

    for (auto &it : _bullet)
        str += it.serialize();

    // Player
    str += "PLAYER;ID:" + std::to_string(this->_id);
    str += ";X:" + std::to_string(this->_pos.x);
    str += ";Y:" + std::to_string(this->_pos.y);
    str += ";R:" + std::to_string(this->_rota);

    return (str += ";\n");
}

void Player::deserialize(std::string str)
{
    int pos = 0;

    pos = str.find("ID:");
    this->_id = std::atof(str.substr((pos + 3), str.find(";", pos) - pos).c_str());
    pos = str.find("X:");
    this->_pos.x = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("Y:");
    this->_pos.y = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("R:");
    this->_rota = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
}

void Player::gest(Client *&client, std::list<BlockObject *> &blocks, Setting setting)
{
    RAYLIB::Vector2 oldPlayerPos = this->_pos;
    static RAYLIB::Vector2 clear = {-1000, -1000};

    this->move(setting);
    this->rotate();
    this->gestColision(blocks, oldPlayerPos);
    if (RAYLIB::IsKeyPressed(RAYLIB::KEY_ONE))
        this->_weaponUse = 1;
    if (RAYLIB::IsKeyPressed(RAYLIB::KEY_TWO))
        this->_weaponUse = 2;
    if (this->_health <= 0) {
        this->setPos(clear);
    }
    if (this->_weaponUse == 1) {
        this->_weapon1->update(this->_pos, this->_rota);
        if (RAYLIB::IsMouseButtonDown(RAYLIB::MOUSE_LEFT_BUTTON)) {
            _bullet.push_back(this->_weapon1->shoot((this->_id + 1) * 1000 + 2 + this->_nbBullet));
            this->_nbBullet += 1;
        }
    } else if (this->_weaponUse == 2) {
        this->_weapon2->update(this->_pos, this->_rota);
        if (RAYLIB::IsMouseButtonDown(RAYLIB::MOUSE_LEFT_BUTTON)) {
            _bullet.push_back(this->_weapon2->shoot((this->_id + 1) * 1000 + 2 + this->_nbBullet));
            this->_nbBullet += 1;
        }
    }

    // if (this->_change) {
        client->send(this->serialize());
    //     this->_change = false;
    // }
}