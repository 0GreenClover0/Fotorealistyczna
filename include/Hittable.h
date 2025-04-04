#pragma once

#include "Material.h"
#include "Ray.h"
#include "Vector.h"

struct HitResult
{
    std::shared_ptr<Material> material = {};
    Vector hitPoint = {};
};

class Hittable
{
public:
    virtual ~Hittable() = default;
    virtual void hit(const Ray& ray, HitResult& hitResult) = 0;

    std::shared_ptr<Material> getMaterial() const;

protected:
    std::shared_ptr<Material> material = {};
};
