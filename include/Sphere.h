#pragma once

#include "Hittable.h"
#include "Vector.h"

class Sphere final : public Hittable
{
public:
    Sphere(const Vector& p, float radius, std::shared_ptr<Material> const& mat);

    virtual void hit(const Ray& ray, HitResult& hitResult) override;

    Vector center;
    float radius;
};
