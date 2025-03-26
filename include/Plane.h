#pragma once
#include "Vector.h"

struct Plane
{
    // Plane and normal
    Plane(const Vector& p, const Vector& normal);
    Plane(float a, float b, float c, float d);

    Vector p = Vector(0, 0, 0);
    Vector normal = Vector(0, 0, 0);
    float d = 0;
};
