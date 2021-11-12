/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** Map3D
*/

#ifndef Map3D_HPP_
#define Map3D_HPP_


#include <vector>
#include <list>

#include "BlockObject.hpp"
#include "Encapsulation/Model.hpp"

class MapBlock : public BlockObject
{
    public:
        MapBlock() = default;
        MapBlock(rl::Models model, RAYLIB::Vector3 pos, float size = 1, bool breakable = false);// : _model(model), _pos(pos), _size(size) {};
        ~MapBlock() = default;

        RAYLIB::Vector2 getPos()  {return {_pos.x, _pos.z};};
        int getId()  {return _id;};
        void setPos(RAYLIB::Vector2 newPosition) {_pos = {newPosition.x, 0, newPosition.y};};
        void setId(int id)  {_id = id;};
        void draw();
        std::string serialize() {return ("");};
        void deserialize(std::string) {};
        rl::Models getModel() const {return _model;};

    private:
        rl::Models _model;
        RAYLIB::Vector3 _pos;
        float _size;
        int _id;
        bool _modelSet = false;
};

class Map3D {
    public:
        Map3D(std::vector<std::vector<char>> map, rl::Models, float = 0.5);
        ~Map3D() = default;

        void draw();

        std::list<MapBlock> _mapBlocks;
        std::list<std::pair<float, float>> _spawns;
        std::list<std::pair<float, float>> _items;
};

#endif /* !Map3D_HPP_ */
