/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GameObject
*/

#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include "IGameObject.hpp"
#include "Client.hpp"
#include <map>

class Lobby;
class Play;

class GameObject : public IGameObject {
    public:
        GameObject(RAYLIB::Vector2 = {0, 0}, int = -1);
        ~GameObject() = default;

        RAYLIB::Vector2 getPos();
        int getId();
        void setPos(RAYLIB::Vector2);
        void setPos(RAYLIB::Vector3);
        void setId(int);
        static void gestData(std::map<int, GameObject *> &, std::string, Client *&, Lobby &);
        static void gestData(std::map<int, GameObject *> &, std::string, int &);
        std::string getObjType() {return(this->_objType);};

    protected:
        std::string _objType;
        RAYLIB::Vector2 _pos;
        int _id;
        bool _change;
        float _ypos = 0;
    private:
};

#endif /* !GAMEOBJECT_HPP_ */
