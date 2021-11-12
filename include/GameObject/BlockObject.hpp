/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** BlockObject
*/

#ifndef BLOCKOBJECT_HPP_
#define BLOCKOBJECT_HPP_

#include <array>
#include "GameObject.hpp"
#include "Encapsulation/Model.hpp"

class BlockObject : public GameObject {
    public:
        BlockObject() = default;
        ~BlockObject() = default;
        virtual RAYLIB::Vector2 getPos() = 0;
        virtual int getId() = 0;
        virtual void setPos(RAYLIB::Vector2 newPosition) = 0;
        virtual void setId(int) = 0;
        virtual rl::Models getModel() const = 0;
        bool isBreakable = false;
    protected:
    private:
};

#endif /* !BLOCKOBJECT_HPP_ */
