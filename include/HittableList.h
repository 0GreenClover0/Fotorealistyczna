#pragma once
#include <memory>
#include <vector>

#include "Hittable.h"

class HittableList : public Hittable
{
public:
    virtual bool hit(const Ray& ray, Interval rayT, HitResult& hitResult) override;
    virtual Vector getNormal(const Vector& hitPoint) const override;
    void add(std::shared_ptr<Hittable> const& hittable);

    std::vector<std::shared_ptr<Hittable>> hittables = {};
};

