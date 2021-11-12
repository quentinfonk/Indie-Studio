/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** InputButton
*/

#ifndef INPUTBUTTON_HPP_
#define INPUTBUTTON_HPP_

#include "Button.hpp"
#include <iostream>

class InputButton {
    public:
        InputButton(const char *path = "", float = 0, float = 0, float = 0, float = 0, int = 0, float = 0, float = 0, float = 0);
        ~InputButton();
        bool isSelected();
        void writeChar();
        void draw();
        std::string getText();

    protected:
    private:
        int _posx;
        int _posy;
        int _height;
        int _width;
        int _maxLen;
        bool _selected;
        std::string _text;
        rl::Text _printText;
        Button _button;
        RAYLIB::Color _color;
        const char *_path;
        RAYLIB::Texture2D _texture;
};

#endif /* !INPUTBUTTON_HPP_ */
