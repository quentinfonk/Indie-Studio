/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Button
*/

#include "Button.hpp"
#include <cstring>

Button::Button(const char *path, float posx, float posy, float width, float height)
{
    int WIN_HEIGHT = RAYLIB::GetScreenHeight();
    int WIN_WIDTH = RAYLIB::GetScreenWidth();

    this->_posx = (int)(posx * WIN_WIDTH) / 100;
    this->_posy = (int)(posy * WIN_HEIGHT) / 100;
    this->_height = (int)(height * WIN_HEIGHT) / 100;
    this->_width = (int)(width * WIN_WIDTH) / 100;
    this->_path = path;
    if (strlen(path) != 0)
        this->_texture = RAYLIB::LoadTexture(path);
}

Button::~Button()
{
}

bool Button::isHover()
{
    RAYLIB::Vector2 pos = RAYLIB::GetMousePosition();

    if (CheckCollisionPointRec(pos, {(float)this->_posx, (float)this->_posy, (float)this->_width, (float)this->_height}))
        return (true);
    return (false);
}

bool Button::isPressed()
{
    if (this->isHover() && RAYLIB::IsMouseButtonDown(RAYLIB::MOUSE_LEFT_BUTTON))
        return (true);
    return (false);
}

bool Button::isClicked()
{
    if (this->isHover() && RAYLIB::IsMouseButtonReleased(RAYLIB::MOUSE_LEFT_BUTTON))
        return (true);
    return (false);
}

void Button::draw()
{
    if (strlen(this->_path) == 0)
        RAYLIB::DrawRectangle(this->_posx, this->_posy, this->_width, this->_height, RAYLIB::DARKGRAY);
    else {
        if (this->isHover())
            RAYLIB::DrawTextureEx(this->_texture, {(float)this->_posx, (float)this->_posy}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::RED);
        else
            RAYLIB::DrawTextureEx(this->_texture, {(float)this->_posx, (float)this->_posy}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    }
}