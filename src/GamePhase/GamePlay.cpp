/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** GamePlay
*/

#include "GamePlay.hpp"
#include "Ai.hpp"
#include "Sound.hpp"

void GamePlay::nonToPoi(std::list<MapBlock> obj)
{
    for (auto it : obj)
        _blocks.push_back(new MapBlock(it));
}

GamePlay::GamePlay()
{
    _FPCamera =  rl::Camera({ 0, 10, 0 }, RAYLIB::CAMERA_FIRST_PERSON);
    _player = Player();
    auto pos = _player.getPos();
    _TopCamera = rl::Camera({pos.x, 6, pos.y});
    this->_weapon = new Pistol(-1, pos);
}

void GamePlay::placeItems(std::list<std::pair<float, float>> itemsPos)
{
    int rand = 0;

    for (auto it : itemsPos) {
        rand = RAYLIB::GetRandomValue(0, enumToItem.size());
        try {
            auto obj = enumToItem.at((EnumItems)rand);
            obj->setPos(RAYLIB::Vector2{it.first, it.second});
            _items.push_back(obj);
        } catch(...) {};
    }
}

GamePhase GamePlay::launch(Setting setting)
{
    //SET ALL
    float size = 1;
    auto mesh = RAYLIB::GenMeshCube(size, size, size);
    auto charMap = main_create_map(5, 1);
    auto texture = RAYLIB::LoadTexture(std::string("assets/texture/wall.png").c_str());
    auto model = rl::Models(mesh, texture);
    auto m = Map3D(charMap, model, size);
    placeItems(m._items);
    _spawns = m._spawns;
    _spawn = m._spawns.front();
    _enemies.push_back(new Ai(charMap));
    _enemies.back()->setPos(RAYLIB::Vector2{_spawns.back().first, _spawns.back().second});
    _player.setPos(RAYLIB::Vector2{_spawn.first, _spawn.second});
    _TopCamera.setPosition({_spawn.first, _TopCamera.getPosition().y, _spawn.second});
    _FPCamera.setPosition({_spawn.first, _FPCamera.getPosition().y, _spawn.second});
    this->_mapSize = {charMap.size(), charMap.front().size()};
    this->nonToPoi(m._mapBlocks);
    return this->restart(setting);
}

float convertSize(float x, int size)
{
    x = (x * 100) / size;
    x = (x * size) / 100;
    return (x);
}

void GamePlay::lifeAndShield()
{
    static int i = 0;
    if (i == 0) {
        this->_shield = RAYLIB::LoadTexture(std::string("assets/texture/shield.png").c_str());
        this->_heart = RAYLIB::LoadTexture(std::string("assets/texture/heart.png").c_str());
        i++;
    }
    RAYLIB::DrawTextureEx(this->_heart, {convertSize(785, RAYLIB::GetScreenWidth()), convertSize(975, RAYLIB::GetScreenHeight())}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    RAYLIB::DrawTextureEx(this->_shield, {convertSize(1055, RAYLIB::GetScreenWidth()), convertSize(975, RAYLIB::GetScreenHeight())}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    RAYLIB::DrawRectangleLines(convertSize(850, RAYLIB::GetScreenWidth()), convertSize(975, RAYLIB::GetScreenHeight()), 200, 60, RAYLIB::BLACK);
    RAYLIB::DrawRectangle(convertSize(851, RAYLIB::GetScreenWidth()), convertSize(976, RAYLIB::GetScreenHeight()), 198, 58, RAYLIB::GRAY);
    RAYLIB::DrawRectangle(convertSize(851, RAYLIB::GetScreenWidth()), convertSize(976, RAYLIB::GetScreenHeight()), (this->_player.getHealth() * 2) - 2, 58, RAYLIB::RED);
    RAYLIB::DrawRectangleLines(convertSize(1120, RAYLIB::GetScreenWidth()), convertSize(975, RAYLIB::GetScreenHeight()), 50, 60, RAYLIB::BLACK);
    RAYLIB::DrawRectangle(convertSize(1121, RAYLIB::GetScreenWidth()), convertSize(976, RAYLIB::GetScreenHeight()), 48, 58, RAYLIB::GRAY);
    if (this->_player.getShield() == 1)
        RAYLIB::DrawRectangle(convertSize(1121, RAYLIB::GetScreenWidth()), convertSize(976, RAYLIB::GetScreenHeight()), 48, 58, RAYLIB::BLUE);
}

GamePhase GamePlay::restart(Setting setting)
{
    GamePhase gamePhase = GamePlayPhase;

    for (auto it: _enemies)
        ((Ai *)(it))->getPriority();

    _oldPlayerPos = _player.getPos();
    //update attrib from server
    if (_player.isAlive()) {
        this->aliveCall(setting);
    } else {
        this->specCall(setting);
    }
    if (RAYLIB::IsKeyPressed(RAYLIB::KEY_P))
        gamePhase = PausePhase;
    this->drawAll();
    RAYLIB::DrawFPS(10, 10);
    lifeAndShield();
    // RAYLIB::ShowCursor();
    return gamePhase;
}

void GamePlay::aliveCall(Setting setting)
{
    this->reloadPower();
    this->updatePowerUp(setting);
    this->updateLocal(setting);
    this->testThings();
}

void GamePlay::specCall(Setting setting)
{
    //todo
    ACTIVE_CAMERA.updateCamera(setting);
}

void GamePlay::drawAll()
{
    RAYLIB::BeginMode3D(ACTIVE_CAMERA.getCamera());

    _weapon->draw();

    this->_player.draw(); // draw self
    // draw all lists
    auto campos = ACTIVE_CAMERA.getPosition();
    for (auto it : this->_blocks) {
        auto pos = it->getPos();
        if ((pos.y < campos.z + _renderDistance && pos.y > campos.z - _renderDistance) && (pos.x < campos.x + _renderDistance && pos.x > campos.x - _renderDistance))
            it->draw();
    }
    for (auto it : this->_enemies)
        it->draw();
    for (auto it : this->_items)
        it->draw();
    for (auto &it : _bullet) {
        it.update();
        it.draw(); // draw
    }
    RAYLIB::DrawPlane({ _mapSize.first / 2, -0.01, _mapSize.second / 2 }, { (_mapSize.first + _mapSize.second) * 10, (_mapSize.second + _mapSize.first) * 10}, GROUNDCOLOR); //draw flor
    for (auto it : _spawns)
        RAYLIB::DrawPlane({ it.first, 0, it.second}, { 1, 1}, SPAWNCOLOR);
    for (auto it : _items)
        RAYLIB::DrawPlane({ it->getPos().x, 0, it->getPos().y}, { 1, 1}, ITEMCOLOR);

    RAYLIB::EndMode3D();
}
