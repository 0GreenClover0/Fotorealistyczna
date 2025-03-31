#pragma once

#include "Line.h"

class Ray
{
public:
    Ray(const Vector& origin, const Vector& direction) : origin(origin), direction(direction) {}

    Vector origin;
    Vector direction;
};
