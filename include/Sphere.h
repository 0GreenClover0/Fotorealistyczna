#pragma once

#include "Hittable.h"
#include "Vector.h"

class Sphere final : public Hittable
{
public:
    Sphere(const Vector& p, float radius);

    virtual Vector hit(const Ray& ray) override;

    Vector center;
    float radius;
};
