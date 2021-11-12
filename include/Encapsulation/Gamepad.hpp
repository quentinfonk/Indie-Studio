/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** gamepad
*/

#ifndef GAMEPAD_HPP_
#define GAMEPAD_HPP_

#include "include.hpp"
#include <list>

class Gamepad
{
    public:
        Gamepad(int id);
        ~Gamepad() = default;

        // Getters and setters
        float getAxisLeftX();
        float getAxisLeftY();
        float getAxisRightX();
        float getAxisRightY();
        std::list<int> getButtonPressed();
        std::pair<float, float> getAxisLeft();
        std::pair<float, float> getAxisRight();
    private:
        int _id;
};

#endif /* !GAMEPAD_HPP_ */
