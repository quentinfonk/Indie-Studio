/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "encapsulation.hpp"

class Button {
    public:
        Button(const char * = "", float = 0, float = 0, float = 0, float = 0);
        ~Button();
        bool isHover();
        bool isPressed();
        bool isClicked();
        void draw();
    protected:
    private:
        int _posx;
        int _posy;
        int _height;
        int _width;
        const char *_path;
        RAYLIB::Texture2D _texture;
};

#endif /* !BUTTON_HPP_ */
