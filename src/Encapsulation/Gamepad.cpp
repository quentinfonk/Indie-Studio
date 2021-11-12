/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Gamepad
*/

#include "Gamepad.hpp"

Gamepad::Gamepad(int id) : _id(id)
{
}

float Gamepad::getAxisLeftX()
{
    return (GetGamepadAxisMovement(this->_id, RAYLIB::GAMEPAD_AXIS_LEFT_X));
}

float Gamepad::getAxisLeftY()
{
    return (GetGamepadAxisMovement(this->_id, RAYLIB::GAMEPAD_AXIS_LEFT_Y));
}

std::pair<float, float> Gamepad::getAxisLeft()
{
    return {this->getAxisLeftX(), this->getAxisLeftY()};
}

float Gamepad::getAxisRightX()
{
    return (GetGamepadAxisMovement(this->_id, RAYLIB::GAMEPAD_AXIS_RIGHT_X));
}

float Gamepad::getAxisRightY()
{
    return (GetGamepadAxisMovement(this->_id, RAYLIB::GAMEPAD_AXIS_RIGHT_Y));
}

std::pair<float, float> Gamepad::getAxisRight()
{
    return {getAxisRightX(), getAxisRightY()};
}

std::list<int> Gamepad::getButtonPressed()
{
    std::list<int> to_ret;

    for (int i = 1; i <= 17; i++)
        if (RAYLIB::IsGamepadButtonDown(this->_id, i))
            to_ret.push_back(i);
    return to_ret;
}
