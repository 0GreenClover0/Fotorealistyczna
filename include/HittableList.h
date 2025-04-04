#pragma once
#include <memory>
#include <vector>

#include "Hittable.h"

class HittableList : public Hittable
{
public:
    virtual void hit(const Ray& ray, HitResult& hitResult) override;
    void addToWorld(std::shared_ptr<Hittable> const& hittable);

private:
    std::vector<std::shared_ptr<Hittable>> hittables = {};
};

