/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Model
*/

#include "Model.hpp"

rl::Models::Models(RAYLIB::Mesh mesh, RAYLIB::Texture2D texture, RAYLIB::Vector3 pos)
{
    _model = LoadModelFromMesh(mesh);
    _model.materials[0].maps[RAYLIB::MATERIAL_MAP_DIFFUSE].texture = texture;
    _height = texture.height;
    _width = texture.width;
    _pos = pos;
}

rl::Models::Models(RAYLIB::Mesh mesh, RAYLIB::Vector3 pos)
{
    _model = LoadModelFromMesh(mesh);
    _pos = pos;
}

rl::Models::Models(std::string filepath, RAYLIB::Vector3 pos)
{
    _model = RAYLIB::LoadModel(filepath.c_str());
    _pos = pos;
}

void rl::Models::draw()
{
    RAYLIB::DrawModel(_model, _pos, 1, RAYLIB::WHITE);
}