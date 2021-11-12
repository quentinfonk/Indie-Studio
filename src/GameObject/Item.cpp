/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Item
*/

#include "Item.hpp"

void game_object::Item::draw()
{
    static int rota = 0;
    auto __bb = RAYLIB::MeshBoundingBox(_model._model.meshes[0]);
    float _z = std::abs(__bb.min.z - __bb.max.z);
    float _x = std::abs(__bb.min.x - __bb.max.x);
    float _y = std::abs(__bb.min.y - __bb.max.y);
    float __v1 = (_z > _x) ? _z : _x;
    float __varForCalculateScale = (__v1 > _y) ? __v1 : _y;
    float scale = std::abs(0.6 / __varForCalculateScale);

    RAYLIB::Vector3 vScale = { scale, scale, scale };
    RAYLIB::Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };
    rota += (100 * RAYLIB::GetFrameTime());
    rota %= 360;
    if (!isWear)
        RAYLIB::DrawModelEx(_model._model, {_pos.x, _ypos, _pos.y}, rotationAxis, rota, vScale, {255, 0, 0, 255});
}