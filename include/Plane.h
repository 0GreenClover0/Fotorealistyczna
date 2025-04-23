#pragma once

#include "Hittable.h"
#include "Vector.h"

class Plane : public Hittable
{
public:
    // Plane and normal
    Plane(const Vector& p, const Vector& normal, std::shared_ptr<Material> const& mat);

    virtual bool hit(const Ray& ray, Interval rayT, HitResult& hitResult) override;
    virtual Vector getNormal(const Vector& hitPoint) const override;

    Vector p = Vector(0, 0, 0);
    Vector normal = Vector(0, 0, 0);
    float d = 0;
};
