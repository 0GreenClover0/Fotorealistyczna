#pragma once
#include <memory>
#include <vector>

#include "Hittable.h"

class HittableList : public Hittable
{
public:
    virtual Vector hit(const Ray& ray) override;
    void addToWorld(std::shared_ptr<Hittable> const& hittable);

private:
    std::vector<std::shared_ptr<Hittable>> hittables = {};
};

