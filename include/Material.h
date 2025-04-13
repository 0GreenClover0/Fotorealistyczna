#pragma once

#include "Vector.h"

enum class MaterialType
{
    Default,
    Reflective,
    Refractive,
};

class Material
{
public:
    explicit Material(Vector diffuse, Vector specular, float shininess = 0.0f, MaterialType matType = MaterialType::Default)
        : diffuse(diffuse), specular(specular), shininess(shininess), materialType(matType) {}
    Vector diffuse = {};
    Vector specular = {};
    float shininess = 1.0f;
    MaterialType materialType = MaterialType::Default;
};
