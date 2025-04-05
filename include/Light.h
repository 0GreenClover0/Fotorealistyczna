#pragma once
#include "Vector.h"

class Light
{
public:
    Light(const Vector& position, const Vector& diffuse, const Vector& specular);

    Vector position = {};
    Vector diffuse = {};
    Vector specular = {};

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
};
