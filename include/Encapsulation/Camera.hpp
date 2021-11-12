/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "include.hpp"
#include <utility>
#include <cmath>

class Setting;

namespace rl {
    // class Camera
    // {
    //     public:
    //         Camera();
    //         Camera(Vector3, CameraMode);
    //         ~Camera();

    //         // Getters & setters
    //         void setPosition(Vector3);
    //         void setTarget(Vector3);
    //         void setFOV(float);
    //         void setProjection(CameraProjection);
    //         void setMode(CameraMode);
    //         Vector3 getPosition(void) const;
    //         Vector3 getTarget(void) const;
    //         float getCameraFOV(void) const;
    //         void updateCamera();

    //         Camera3D _camera;
    //     protected:
    //     private:
    //         Vector3 _pos;
    //         Vector3 _target;
    //         CameraProjection _projection;
    //         CameraMode _mode;
    //         float _fov;
    // };
    class Camera {
        public:
            Camera(RAYLIB::Vector3 pos = {0, 0, 0}, RAYLIB::CameraMode mode = RAYLIB::CAMERA_FREE);
            ~Camera() = default;

            void setPosition(RAYLIB::Vector3 value) {_camera.position = value;};
            void setTarget(RAYLIB::Vector3 value) {_camera.target = value;};
            void setFOV(float value) {_camera.fovy = value;};
            void setProjection(RAYLIB::CameraProjection value) {_camera.projection = value;};
            void setMode(RAYLIB::CameraMode mode) {SetCameraMode(_camera, mode); _mode = mode;};
            void setSpeed(int speed) {_speed = speed;};
            
            RAYLIB::Vector3 getPosition(void) const {return _camera.position;};
            RAYLIB::Vector3 getTarget(void) const {return _camera.target;};
            float getCameraFOV(void) const {return _camera.fovy;};
            RAYLIB::Camera3D getCamera() const {return _camera;};
            int getSpeed() const {return _speed;};

            void updateCamera(Setting, std::pair<float, float> gmpAxisLeft = {0, 0}, std::pair<float, float> gmpAxisRight = {0.0f, 0.0f});

        private:
            void __fpUpdateCamera(Setting, std::pair<float, float> gmpAxisLeft = {0, 0}, std::pair<float, float> gmpAxisRight = {0.0f, 0.0f});
            void __freeUpdateCamera(std::pair<float, float> gmpAxisLeft = {0, 0}, std::pair<float, float> gmpAxisRight = {0.0f, 0.0f});
        private:
            RAYLIB::Camera3D _camera;
            std::pair<float, float> assignpr(float value, float x, float y);
            std::pair<float, float> getpr(float x, float y);
            int _speed = 90;
            RAYLIB::CameraMode _mode;
    };
};

#endif /* !CAMERA_HPP_ */
