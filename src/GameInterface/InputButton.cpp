/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** InputButton
*/

#include "InputButton.hpp"
#include <cstring>

InputButton::InputButton(const char *path, float posx, float posy, float width, float height, int maxLen, float textx, float texty, float textlengh)
{
    int WIN_HEIGHT = RAYLIB::GetScreenHeight();
    int WIN_WIDTH = RAYLIB::GetScreenWidth();

    this->_posx = (int)(posx * WIN_WIDTH) / 100;
    this->_posy = (int)(posy * WIN_HEIGHT) / 100;
    this->_height = (int)(height * WIN_HEIGHT) / 100;
    this->_width = (int)(width * WIN_WIDTH) / 100;
    this->_maxLen = maxLen;
    this->_selected = false;
    this->_button = Button(path, posx, posy, width, height);
    this->_color = Fade(RAYLIB::ORANGE, 0.6);
    this->_printText = rl::Text("", textx, texty, textlengh, RAYLIB::BLACK);
    this->_path = path;
    if (strlen(path) != 0)
        this->_texture = RAYLIB::LoadTexture(path);
}

InputButton::~InputButton()
{
}

bool InputButton::isSelected()
{
    if (this->_button.isClicked()) {
        this->_selected = true;
        this->_color = Fade(RAYLIB::ORANGE, 1);
    }
    if (RAYLIB::IsMouseButtonDown(RAYLIB::MOUSE_LEFT_BUTTON) && !this->_button.isHover()) {
        this->_selected = false;
        this->_color = Fade(RAYLIB::ORANGE, 0.6);
    }
    return (this->_selected);
}

void InputButton::writeChar()
{
    int key = RAYLIB::GetCharPressed();

    while (key > 0) {
        if ((key >= 32) && (key <= 125) && ((int)this->_text.size() < this->_maxLen))
            this->_text += (char)key;
        key = RAYLIB::GetCharPressed();
    }
    if (RAYLIB::IsKeyPressed(RAYLIB::KEY_BACKSPACE) && this->_text.size() > 0)
        this->_text.pop_back();
    this->_printText.setText(this->_text);
}

void InputButton::draw()
{
    if (strlen(this->_path) != 0 && this->_selected == false)
        RAYLIB::DrawTextureEx(this->_texture, {(float)this->_posx, (float)this->_posy}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    else if (strlen(this->_path) != 0 && this->_selected == true)
        RAYLIB::DrawTextureEx(this->_texture, {(float)this->_posx, (float)this->_posy}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::RED);
    else if (strlen(this->_path) == 0) {
        RAYLIB::DrawRectangle(this->_posx, this->_posy, this->_width, this->_height, this->_color);
        RAYLIB::DrawRectangle(this->_posx + this->_height * 0.08, this->_posy + this->_height * 0.08, this->_width - this->_height * 0.16, this->_height - this->_height * 0.16, RAYLIB::DARKGRAY);
    }
    this->_printText.draw();
}

std::string InputButton::getText()
{
    return (this->_text);
}