/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** model
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "include.hpp"

namespace rl {
    class Models
    {
        public:
            Models() = default;
            Models(std::string,  RAYLIB::Vector3 = {0, 0, 0});
            Models(RAYLIB::Mesh, RAYLIB::Texture2D, RAYLIB::Vector3 = {0, 0, 0});
            Models(RAYLIB::Mesh, RAYLIB::Vector3 = {0, 0, 0});
            ~Models() = default;
            void draw();
            void setPos(RAYLIB::Vector3 pos) {_pos = pos;};
            RAYLIB::Model &getModel() {return _model;};
            RAYLIB::Model _model;

        private:
            int _height;
            int _width;
            RAYLIB::Vector3 _pos;
    };
};

#endif /* !MODEL_HPP_ */
