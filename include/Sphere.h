#pragma once

#include "Hittable.h"
#include "Vector.h"

class Sphere final : public Hittable
{
public:
    Sphere(const Vector& p, float radius, std::shared_ptr<Material> const& mat);

    virtual bool hit(const Ray& ray, Interval rayT, HitResult& hitResult) override;
    virtual Vector getNormal(const Vector& hitPoint) const override;

    Vector center;
    float radius;
};
