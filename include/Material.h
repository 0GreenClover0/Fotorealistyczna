#pragma once

#include "Vector.h"

class Material
{
public:
    explicit Material(Vector color, float shininess = 0.0f) : color(color), shininess(shininess) {}
    Vector color = {};
    float shininess = 1.0f;
};
