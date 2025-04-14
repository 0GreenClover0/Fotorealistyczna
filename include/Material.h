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
    Material() = default;
    explicit Material(Vector diffuse, Vector specular, float shininess = 0.0f, MaterialType matType = MaterialType::Default, float iorefr = 1.0f)
        : diffuse(diffuse), specular(specular), shininess(shininess), ior(iorefr), materialType(matType) {}
    Vector diffuse = {};
    Vector specular = {};
    float shininess = 1.0f;
    float ior = 1.0f;   // Index of refraction, applied only when the material is refractive
    MaterialType materialType = MaterialType::Default;
};
