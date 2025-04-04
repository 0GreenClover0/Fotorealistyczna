#pragma once
#include "Vector.h"

class Light
{
public:
    Light(const Vector& position, const Vector& color, const float intensity);

    Vector position;
    Vector color;
    float intensity;
};
