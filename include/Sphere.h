#pragma once

#include "Vector.h"

class Sphere
{
public:
    Sphere(const Vector& p, float radius);

    Vector point;
    float radius;
};
