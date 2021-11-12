/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Window
*/

#include "Window.hpp"

// ------ Méthodes spéciales ------
rl::Window::Window()
{
    rl::Window(900, 450, "");
}

rl::Window::Window(const std::string windowName)
{
    rl::Window(900, 450, windowName);
}

rl::Window::Window(const int width, const int height)
{
    rl::Window(width, height, "");
}

rl::Window::Window(const int width, const int height, const std::string msg)
{
    RAYLIB::InitWindow(width, height, msg.c_str());
    this->setFps();
    RAYLIB::Image image = RAYLIB::LoadImage("assets/texture/icon.png");
    RAYLIB::ImageFormat(&image, RAYLIB::PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    RAYLIB::SetWindowIcon(image);
}

// ------ Getters & setters ------
void rl::Window::setFps(const int fps)
{
    this->_fps = fps;
    RAYLIB::SetTargetFPS(fps);
}

int rl::Window::getFps()
{
    return (this->_fps);
}

int rl::Window::getWidth()
{
    return RAYLIB::GetScreenWidth();
}

int rl::Window::getHeight()
{
    return RAYLIB::GetScreenHeight();
}


// ------ Méthodes ------
void rl::Window::fullscreen()
{
    RAYLIB::ToggleFullscreen();
}

bool rl::Window::loop()
{
    if (RAYLIB::IsKeyDown(RAYLIB::KEY_ESCAPE) || RAYLIB::IsKeyPressed(RAYLIB::KEY_ESCAPE) || RAYLIB::IsKeyReleased(RAYLIB::KEY_ESCAPE))
        return (false);
    return (true);
}

void rl::Window::clear(RAYLIB::Color color)
{
    RAYLIB::ClearBackground(color);
}

void rl::Window::destroy()
{
    RAYLIB::CloseWindow();
}

void rl::Window::loading()
{
    RAYLIB::Texture2D tex = RAYLIB::LoadTexture("assets/texture/loading.png");
    RAYLIB::BeginDrawing();
    DrawTextureEx(tex, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    RAYLIB::EndDrawing();
    RAYLIB::UnloadTexture(tex);
}