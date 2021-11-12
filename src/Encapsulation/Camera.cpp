/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Camera
*/

#include "Camera.hpp"
#include <iostream>
#include <raylib.h>
#include <MyRayMath.hpp>
#include "Setting.hpp"

std::pair<float, float> rl::Camera::getpr(float x, float z)
{
    x = std::abs(x);
    z = std::abs(z);
    float globalValue = x + z;
    float xr = x * 100 / globalValue;
    float zr = xr - 100;
    return {std::abs(xr), std::abs(zr)};
}

std::pair<float, float> rl::Camera::assignpr(float value, float x, float y)
{
    return {value * (x / 100), value * (y / 100)};
}

rl::Camera::Camera(RAYLIB::Vector3 pos, RAYLIB::CameraMode mode)
{
    this->setPosition(pos);
    this->setTarget( {0.0f, 0.0f, 0.0f} );
    _camera.up = {0.0f, 1.0f, 0.0f};
    this->setFOV(45.0);
    this->setProjection(RAYLIB::CAMERA_PERSPECTIVE);
    this->setMode(mode);
}

RAYLIB::Vector2 axToMouse(std::pair<float, float> ax)
{
    static float x = RAYLIB::GetMousePosition().x;
    static float y = RAYLIB::GetMousePosition().y;

    x += ax.first;
    y += ax.second;
    RAYLIB::Vector2 vec = {x, y};
    return (vec);
}

// RAYMATH
void rl::Camera::updateCamera(Setting setting, std::pair<float, float> gmpAxisLeft, std::pair<float, float> gmpAxisRight)
{
    switch (this->_mode) {
        case RAYLIB::CAMERA_FIRST_PERSON:
            __fpUpdateCamera(setting, gmpAxisLeft, gmpAxisRight);
            return;
        case RAYLIB::CAMERA_FREE:
            __freeUpdateCamera(gmpAxisLeft, gmpAxisRight);
            return;
        default :
            RAYLIB::UpdateCamera(&(this->_camera));
            return;
    }
}

void rl::Camera::__freeUpdateCamera(std::pair<float, float> pos, std::pair<float, float> false_rota)
{
    this->setPosition({pos.first - 0.01f, 10, pos.second});
    this->setTarget({pos.first, 0, pos.second});
    (void)false_rota;
}

void rl::Camera::__fpUpdateCamera(Setting setting, std::pair<float, float> gmpAxisLeft, std::pair<float, float> gmpAxisRight)
{
    //udate pos cam from left axis gamepad
        // add keyboard
        if (gmpAxisLeft == std::make_pair(0.0f, 0.0f))
            gmpAxisLeft = {RAYLIB::IsKeyDown(setting.getRight()) - RAYLIB::IsKeyDown(setting.getLeft()), RAYLIB::IsKeyDown(setting.getBackward()) - RAYLIB::IsKeyDown(setting.getForward())};
        if (gmpAxisLeft != std::make_pair(0.0f, 0.0f)) {
            gmpAxisLeft.second *= (1 + RAYLIB::IsKeyDown(RAYLIB::KEY_LEFT_SHIFT));
            gmpAxisLeft.first *= (1 + RAYLIB::IsKeyDown(RAYLIB::KEY_LEFT_SHIFT));
            RAYLIB::Vector3 forward = Vector3Subtract(this->getTarget(), this->getPosition());
            forward.y = 0;
            forward = Vector3Normalize(forward);
            RAYLIB::Vector3 right = {forward.z * -1.0f, 0, forward.x};
            // RAYLIB::Vector3 oldPosition = this->getPosition();

            this->setPosition(Vector3Add(this->getPosition(), Vector3Scale(forward, gmpAxisLeft.second * -1 * RAYLIB::GetFrameTime() * 5))); // 0.0075f is the speed bride
            this->setPosition(Vector3Add(this->getPosition(), Vector3Scale(right, gmpAxisLeft.first * RAYLIB::GetFrameTime() * 5)));
        }

    // set the camera target(view)
        static RAYLIB::Vector2 previousMousePosition = RAYLIB::GetMousePosition();
        auto mouspos = RAYLIB::GetMousePosition();
        gmpAxisRight.first -= (previousMousePosition.x - mouspos.x); 
        gmpAxisRight.second -= (previousMousePosition.y - mouspos.y);
        static RAYLIB::Vector2 previousAxisRightPosition = axToMouse(gmpAxisRight);
        static const int mouseSensivity = 5;
        static const float minimumY = -65.0f;
        static const float maximumY = 89.0f;
        static RAYLIB::Vector2 angle = {0, 0};
        RAYLIB::Vector2 mouseRealPos = Vector2Subtract(previousMousePosition, RAYLIB::GetMousePosition());
        mouseRealPos.x *= -1;
        RAYLIB::Vector2 AxisRightPositionDelta = Vector2Subtract(previousAxisRightPosition, axToMouse(gmpAxisRight));
        // AxisRightPositionDelta = Vector2Add(AxisRightPositionDelta, mouseRealPos);
        float turnRotation = gmpAxisRight.first;
        float tiltRotation = gmpAxisRight.second;
        previousAxisRightPosition = axToMouse(gmpAxisRight);

        if (turnRotation != 0)
            angle.x -= turnRotation * DEG2RAD / mouseSensivity;
        else
            angle.x += AxisRightPositionDelta.x / -mouseSensivity;
        if (tiltRotation)
            angle.y += tiltRotation * DEG2RAD / mouseSensivity;
        else
            angle.y += AxisRightPositionDelta.y / -mouseSensivity;

        if (angle.y < minimumY * DEG2RAD)
            angle.y = minimumY * DEG2RAD;
        else if (angle.y > maximumY * DEG2RAD)
            angle.y = maximumY * DEG2RAD;
        RAYLIB::Vector3 vec = {0, 0, 1};
        RAYLIB::Vector3 vec2 = {-angle.y, -angle.x, 0};
        RAYLIB::Vector3 target = Vector3Transform(vec, MatrixRotateXYZ( vec2 ));
        this->setTarget(Vector3Add(this->getPosition(), target));
        previousMousePosition = RAYLIB::GetMousePosition();
    //end sett camera target
}