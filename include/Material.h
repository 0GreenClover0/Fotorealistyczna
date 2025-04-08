#pragma once

#include "Vector.h"

class Material
{
public:
    explicit Material(Vector diffuse, Vector specular, float shininess = 0.0f) : diffuse(diffuse), specular(specular), shininess(shininess) {}
    Vector diffuse = {};
    Vector specular = {};
    float shininess = 1.0f;
};
