#pragma once

#include "Vector.h"

class Ray
{
public:
    Ray() = default;
    Ray(const Vector& origin, const Vector& direction) : origin(origin), direction(direction) {}
    //Ray(const Vector& origin, const Vector& direction, std::shared_ptr<Material> const& mType) : origin(origin), direction(direction), currentMaterial(mType) {}

    Vector origin;
    Vector direction;
    //std::shared_ptr<Material> currentMaterial = {};
};
