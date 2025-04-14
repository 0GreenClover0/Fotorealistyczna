#pragma once
#include "Line.h"
#include "Material.h"

class Ray
{
public:
    Ray(const Vector& origin, const Vector& direction) : origin(origin), direction(direction), currentMaterial(std::make_shared<Material>()) {}
    Ray(const Vector& origin, const Vector& direction, std::shared_ptr<Material> const& mType) : origin(origin), direction(direction), currentMaterial(mType) {}

    Vector origin;
    Vector direction;
    std::shared_ptr<Material> currentMaterial = {};
};
