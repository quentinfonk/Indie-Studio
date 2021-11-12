/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Weapon
*/

#include "Weapon.hpp"
#include <cmath>


std::pair<float, float> pointInACircle(float angle, float radius)
{

    angle *= PI;

    float x = radius * std::cos(angle / 180);
    float y = radius * std::sin(angle / 180);

    return {x, y};
}

float coefDirector(std::pair<float, float> origine, std::pair<float, float> nextPoint)
{
    float x = nextPoint.first + origine.first;
    float y = nextPoint.second + origine.second;

    return y / x;
}

Bullet::Bullet()
{
    isReal = false;
}

Bullet::Bullet(int id, RAYLIB::Vector3 pos, float rota, float cone, float damage, float speed)
{
    RAYLIB::Mesh mesh = RAYLIB::GenMeshSphere(0.05, 16, 16);
    rl::Models bulletModel = rl::Models(mesh);

    _model = bulletModel;
    this->setPos(pos);
    _rota = RAYLIB::GetRandomValue(rota - cone, rota + cone);
    _damage = (int) damage;
    _speed = speed;
    this->update(0.35);
    this->_id = id;
    this->_objType = "Bullet";
}

void Bullet::update(float radius)
{
    if (!isReal)
        return;
    if (std::isnan(radius))
        radius = this->_speed * RAYLIB::GetFrameTime();
    auto pt = pointInACircle(this->_rota, (radius));
    this->_pos.x += pt.first;
    this->_pos.y -= pt.second;
}

void Bullet::draw()
{
    if (isReal)
        RAYLIB::DrawModel(_model._model, {_pos.x, _ypos, _pos.y}, 1, RAYLIB::BLACK);
}

std::string Bullet::serialize()
{
    if (!this->isReal)
        return ("");
    std::string str;

    str += "BULLET;ID:" + std::to_string(this->_id);
    str += ";X:" + std::to_string(this->_pos.x);
    str += ";Y:" + std::to_string(this->_ypos);
    str += ";Z:" + std::to_string(this->_pos.y);
    str += ";DA:" + std::to_string(this->_damage);

    return (str += ";\n");
}

void Bullet::deserialize(std::string str)
{
    int pos = 0;

    pos = str.find("ID:");
    this->_id = std::atof(str.substr((pos + 3), str.find(";", pos) - pos).c_str());
    pos = str.find("X:");
    this->_pos.x = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("Y:");
    this->_ypos = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("Z:");
    this->_pos.y = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("DA:");
    this->_damage = std::atof(str.substr((pos + 3), str.find(";", pos) - pos).c_str());
}


Bullet Weapon::shoot(int id_bullet)
{
    
    static rl::Sound music = rl::Sound();
    static auto lastShoot = TIMENOW;
    static bool first = true;
    if (first);
    else if (!this->_wear || !this->_nbBullet || CHRONO(lastShoot) < this->_time_shoot)
        return Bullet();
    if (this->getObjType() == "Rifle")
        music.playRiffleShoot();
    else if (this->getObjType() == "Pistol")
        music.playGunShoot();
    else if (this->getObjType() == "Snip")
        music.playSniperShoot();
    first = false;
    lastShoot = TIMENOW;
    this->_nbBullet -= 1;
    return Bullet(id_bullet, {this->_pos.x, _ypos, _pos.y}, this->_rota - 90, this->_cone, this->_damage, this->_bullet_speed);
}

void Weapon::update(RAYLIB::Vector2 pos, float rota)
{
    if (!_wear)
        return;
    this->_rota = rota;
    std::pair<float, float> circlePos = pointInACircle(std::abs(rota), 0.2);
    this->_pos.x = pos.x + circlePos.first;
    this->_pos.y = pos.y + circlePos.second;
    this->_ypos = 0.1;
}

std::string Weapon::serialize()
{
    std::string str;

    str += "WEAPON;ID:" + std::to_string(this->_id);
    str += ";TYPE:" + this->_type;
    str += ";X:" + std::to_string(this->_pos.x);
    str += ";Y:" + std::to_string(this->_ypos);
    str += ";Z:" + std::to_string(this->_pos.y);
    str += ";R:" + std::to_string(this->_rota);

    return (str += ";\n");
}

void Weapon::deserialize(std::string str)
{
    int pos = 0;

    pos = str.find("ID:");
    this->_id = std::atof(str.substr((pos + 3), str.find(";", pos) - pos).c_str());
    pos = str.find("TYPE:");
    this->_type = str.substr((pos + 5), str.find(";", pos) - pos);
    pos = str.find("X:");
    this->_pos.x = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("Y:");
    this->_ypos = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("Z:");
    this->_pos.y = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("R:");
    this->_rota = std::atof(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
}

void Weapon::draw()
{
    float scale = 0.1;
    RAYLIB::Vector3 vScale = { scale, scale, scale };
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };

    RAYLIB::DrawModelEx(_model._model, {_pos.x, _ypos, _pos.y}, rotationAxis, _rota, vScale, RAYLIB::WHITE);
}

Pistol::Pistol(int id, RAYLIB::Vector2 pos)
{
    static rl::Models pistol_model = rl::Models("assets/weapons/Glock18/Glock18.obj");

    _model = pistol_model;
    this->_nbBullet = 65535;
    this->_pos = pos;
    _ypos = 0.1;
    this->_time_shoot = 500;
    this->_bullet_speed = 15;
    this->_damage = 15;
    this->_cone = 5;
    this->_id = id;
    _type = "PISTOL";
    this->_objType = "Pistol";
}

Rifle::Rifle(int id, RAYLIB::Vector2 pos)
{
    static rl::Models rifle_model = rl::Models("assets/weapons/M4/M4.obj");

    _model = rifle_model;
    this->_nbBullet = 35;
    this->_pos = pos;
    _ypos = 0.1;
    this->_time_shoot = 100;
    this->_bullet_speed = 20;
    this->_damage = 12;
    this->_cone = 10;
    this->_id = id;
    _type = "RIFLE";
    this->_objType = "Rifle";
}

Snip::Snip(int id, RAYLIB::Vector2 pos)
{
    static rl::Models snip_model = rl::Models("assets/weapons/L115A3/L115A3.obj");

    _model = snip_model;
    this->_nbBullet = 6;
    this->_pos = pos;
    _ypos = 0.1;
    this->_time_shoot = 1500;
    this->_bullet_speed = 30;
    this->_damage = 70;
    this->_cone = 0;
    this->_id = id;
    _type = "SNIP";
    this->_objType = "Snip";
}

bool operator==(Bullet f, Bullet s)
{
    auto fPos = f.getPos();
    auto sPos = s.getPos();

    if (fPos.x == sPos.x && fPos.y == sPos.y)
        return true;
    return false;
}