/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Ai
*/

#include "Ai.hpp"
#include <string>
#include <cstdlib>
#include <ctime>

bool compareVector(RAYLIB::Vector2 first_vector, RAYLIB::Vector2 second_vector)
{
    if (int(first_vector.x) == int(second_vector.x) && int(first_vector.y) == int(second_vector.y))
        return true;
    return false;
}

Ai::Ai(std::vector<std::vector<char>> map)
{
    static auto globalPlayerModel = rl::Models("assets/character/character.obj");
    static auto __bb = RAYLIB::MeshBoundingBox(globalPlayerModel._model.meshes[0]);
    static float __varForCalculateScale = __bb.min.z - __bb.max.z;
    this->_scale = std::abs(0.3 / __varForCalculateScale);
    this->_model = globalPlayerModel;
    this->map = map;
    this->_rota = 0;
    this->targetStatus = UNDEFINED;
    this->_weapon1 = new Pistol();
    this->targetPosition.x = 0;
    this->targetPosition.y = 0;
}

void Ai::getPriority()
{
    Target status = checkEnemy();

    if (status == IN_RANGE && this->targetStatus != IN_RANGE)
        attackEnemy();
    else if (status == ABSENT && (this->targetStatus == UNDEFINED || this->targetStatus == ABSENT))
        setRandomTarget();
    moveToNextTile();
}

void Ai::setRandomTarget()
{
    this->open.clear();
    std::srand(std::time(nullptr));
    getAvailableTiles();

    if (open.size() == 0)
        this->targetPosition = this->_pos;
    else
        this->targetPosition = this->open[std::rand() % this->open.size()];
    this->targetStatus = MOVING;
}

void Ai::moveToNextTile()
{
    std::pair<float, float> move(0, 0);
    float speed = 5;

    if (compareVector(this->_pos, this->targetPosition)) {
        this->targetStatus = ABSENT;
        return;
    }
    if (move == std::make_pair(0.0f, 0.0f)) {
        move.first += calculateDistObj(1);
        move.second += calculateDistObj(2);
        move.first *= RAYLIB::GetFrameTime();
        move.second *= RAYLIB::GetFrameTime();
    }
    this->last_pos = this->_pos;
    this->_pos = {this->_pos.x + move.first * speed, this->_pos.y + move.second * speed};
    rotate();
}

Target Ai::checkEnemy()
{
    return ABSENT;
}

void Ai::rotate()
{
    std::pair<int ,int> look;

    look.first = int(this->targetPosition.x) - int(this->_pos.x);
    look.second = int(this->targetPosition.y) - int(this->_pos.y);
    if (look.first == -1)
        look.first = 270;
    else if (look.first == 0)
        look.first = -1;
    else if ( look.first == 1)
        look.first = 90;
    if (look.second == -1)
        look.second = 180;
    else if (look.second == 0)
        look.second = -1;
    else if (look.second == 1)
        look.second = 0;
    if (look.first == -1)
        this->_rota = look.second;
    else if (look.second == -1)
        this->_rota = look.first;
    else
        this->_rota = (look.first + look.second) / 2;
}

int Ai::calculateDistObj(unsigned int axis)
{
    if (axis == 1)
        return int(this->targetPosition.x) - int(this->_pos.x);
    else
        return int(this->targetPosition.y) - int(this->_pos.y);
}

void Ai::getAvailableTiles()
{
    std::vector<RAYLIB::Vector2> children;

    if (isIndexValid(-1, -1))
        children.push_back({this->_pos.x - 1, this->_pos.y - 1});
    if (isIndexValid(-1, 0))
        children.push_back({this->_pos.x - 1, this->_pos.y});
    if (isIndexValid(-1, 1))
        children.push_back({this->_pos.x - 1, this->_pos.y + 1});
    if (isIndexValid(0, -1))
        children.push_back({this->_pos.x, this->_pos.y - 1});
    if (isIndexValid(0, 1))
        children.push_back({this->_pos.x, this->_pos.y + 1});
    if (isIndexValid(1, -1))
        children.push_back({this->_pos.x + 1, this->_pos.y - 1});
    if (isIndexValid(1, 0))
        children.push_back({this->_pos.x + 1, this->_pos.y});
    if (isIndexValid(1, 1))
        children.push_back({this->_pos.x + 1, this->_pos.y + 1});
    for (unsigned int i = 0; i < children.size(); i++)
        if (!compareVector(children[i], last_pos) && isTileValid({children[i].x, children[i].y}))
            this->open.push_back(children[i]);
}

bool Ai::isIndexValid(int x, int y)
{
    if (!(this->_pos.x + x < this->map.size() && this->_pos.x + x > 0))
        return false;
    if (!(this->_pos.y + y < this->map[0].size() && this->_pos.y + y > 0))
        return false;
    return true;
}

bool Ai::isInMap(RAYLIB::Vector2 tile)
{
    if (tile.x < this->map.size() && tile.y < this->map[0].size())
        return true;
    return false;
}

bool Ai::isTileValid(RAYLIB::Vector2 tile)
{
    std::string valid_types = " SPvN";

    for (unsigned int i = 0; i < valid_types.size(); i++)
        if (valid_types[i] == this->map[tile.x][tile.y])
            return true;
    return false;
}

RAYLIB::Vector2 Ai::getEnemyPosition()
{
    RAYLIB::Vector2 pos = {0, 0};

    return pos;
}

void Ai::attackEnemy()
{
    printf("ATTACK\n");
}

std::string Ai::serialize()
{
    std::string str;

    str += "AI;ID:" + std::to_string(this->_id);
    str += ";X:" + std::to_string(this->_pos.x);
    str += ";Y:" + std::to_string(this->_pos.y);

    return (str += "\n");
}

void Ai::deserialize(std::string str)
{
    int pos = 0;

    pos = str.find("X:");
    this->_pos.x = std::atoi(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
    pos = str.find("Y:");
    this->_pos.y = std::atoi(str.substr((pos + 2), str.find(";", pos) - pos).c_str());
}