#pragma once

#include "Interval.h"
#include "Material.h"
#include "Ray.h"
#include "Vector.h"

class Hittable;

struct HitResult
{
    std::shared_ptr<Hittable> hittable = {};
    Vector hitPoint = {};
};

class Hittable
{
public:
    virtual ~Hittable() = default;
    virtual void hit(const Ray& ray, Interval rayT, HitResult& hitResult) = 0;
    virtual Vector getNormal(const Vector& hitPoint) const = 0;

    std::shared_ptr<Material> getMaterial() const;

protected:
    std::shared_ptr<Material> material = {};
};
