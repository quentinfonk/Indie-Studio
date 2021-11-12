/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** IGameObject
*/

#ifndef IGAMEOBJECT_HPP_
#define IGAMEOBJECT_HPP_

#include <iostream>
#include "include.hpp"

class IGameObject {
    public:
        ~IGameObject() = default;
        virtual int getId() = 0;
        virtual void setPos(RAYLIB::Vector2) = 0;
        virtual void setId(int) = 0;
        virtual void draw() = 0;
        virtual std::string serialize() = 0;
        virtual void deserialize(std::string) = 0;
        virtual std::string getObjType() = 0;

    protected:
    private:
};

#endif /* !IGAMEOBJECT_HPP_ */
