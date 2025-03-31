#pragma once

#include "Ray.h"
#include "Vector.h"

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual Vector hit(const Ray& ray) = 0;
};
