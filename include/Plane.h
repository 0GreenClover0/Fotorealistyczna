#pragma once

#include "Hittable.h"
#include "Vector.h"

class Plane : public Hittable
{
public:
    // Plane and normal
    Plane(const Vector& p, const Vector& normal);
    Plane(float a, float b, float c, float d);

    virtual Vector hit(const Ray& ray) override;

    Vector p = Vector(0, 0, 0);
    Vector normal = Vector(0, 0, 0);
    float d = 0;
};
