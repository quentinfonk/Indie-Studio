/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "include.hpp"

namespace rl {
    class Text
    {
        public:
            Text(std::string = "", float = 0, float = 0, float = 15, RAYLIB::Color = RAYLIB::WHITE);
            ~Text() = default;

            // Getters & setters
            void setText(std::string);
            void setPosX(int);
            void setPosY(int);
            void setPos(int, int);
            void setFontSize(int val);
            int getPosX(void);
            int getPosY(void);
            std::pair<int, int> getPos();

            // Méthodes
            void draw();

        private :
            std::string _text;
            int _posx = 0;
            int _posy = 0;
            int _font_size = 15;
            RAYLIB::Color _color;
    };
}

#endif /* !TEXT_HPP_ */
