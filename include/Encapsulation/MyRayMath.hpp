/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** MyRayMath
*/

#ifndef MYRAYMATH_H_
#define MYRAYMATH_H_

namespace RAYLIB {
    #include <raylib.h>
}
#include <cmath>

RAYLIB::Vector2 Vector2Add(RAYLIB::Vector2 v1, RAYLIB::Vector2 v2)
{
    RAYLIB::Vector2 result = { v1.x + v2.x, v1.y + v2.y };
    return result;
}

RAYLIB::Vector2 Vector2Subtract(RAYLIB::Vector2 v1, RAYLIB::Vector2 v2)
{
    RAYLIB::Vector2 result = { v1.x - v2.x, v1.y - v2.y };
    return result;
}

RAYLIB::Vector3 Vector3Add(RAYLIB::Vector3 v1, RAYLIB::Vector3 v2)
{
    RAYLIB::Vector3 result = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return result;
}

RAYLIB::Vector3 Vector3Subtract(RAYLIB::Vector3 v1, RAYLIB::Vector3 v2)
{
    RAYLIB::Vector3 result = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return result;
}

RAYLIB::Vector3 Vector3Scale(RAYLIB::Vector3 v, float scalar)
{
    RAYLIB::Vector3 result = { v.x*scalar, v.y*scalar, v.z*scalar };
    return result;
}

float Vector3Length(const RAYLIB::Vector3 v)
{
    float result = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
    return result;
}

RAYLIB::Vector3 Vector3Transform(RAYLIB::Vector3 v, RAYLIB::Matrix mat)
{
    RAYLIB::Vector3 result = {0, 0, 0};
    float x = v.x;
    float y = v.y;
    float z = v.z;

    result.x = mat.m0*x + mat.m4*y + mat.m8*z + mat.m12;
    result.y = mat.m1*x + mat.m5*y + mat.m9*z + mat.m13;
    result.z = mat.m2*x + mat.m6*y + mat.m10*z + mat.m14;

    return result;
}

RAYLIB::Matrix MatrixIdentity(void)
{
    RAYLIB::Matrix result = { 1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f };

    return result;
}

RAYLIB::Matrix MatrixRotateXYZ(RAYLIB::Vector3 ang)
{
    RAYLIB::Matrix result = MatrixIdentity();

    float cosz = cosf(-ang.z);
    float sinz = sinf(-ang.z);
    float cosy = cosf(-ang.y);
    float siny = sinf(-ang.y);
    float cosx = cosf(-ang.x);
    float sinx = sinf(-ang.x);

    result.m0 = cosz*cosy;
    result.m4 = (cosz*siny*sinx) - (sinz*cosx);
    result.m8 = (cosz*siny*cosx) + (sinz*sinx);

    result.m1 = sinz*cosy;
    result.m5 = (sinz*siny*sinx) + (cosz*cosx);
    result.m9 = (sinz*siny*cosx) - (cosz*sinx);

    result.m2 = -siny;
    result.m6 = cosy*sinx;
    result.m10= cosy*cosx;

    return result;
}

RAYLIB::Vector3 Vector3Normalize(RAYLIB::Vector3 v)
{
    RAYLIB::Vector3 result = v;

    float length, ilength;
    length = Vector3Length(v);
    if (length == 0.0f) length = 1.0f;
    ilength = 1.0f/length;

    result.x *= ilength;
    result.y *= ilength;
    result.z *= ilength;

    return result;
}


#endif /* !MYRAYMATH_H_ */
