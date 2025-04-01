#pragma once

#include "Hittable.h"
#include "Vector.h"

class Sphere final : public Hittable
{
public:
    Sphere(const Vector& p, float radius, std::shared_ptr<Material> const& mat);

    virtual HitResult hit(const Ray& ray) override;

    Vector center;
    float radius;
};
