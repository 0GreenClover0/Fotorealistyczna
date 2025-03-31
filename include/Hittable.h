#pragma once

#include <memory>
#include <vector>

#include "Ray.h"
#include "Vector.h"

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual Vector hit(const Ray& ray) = 0;
};

class HittableList : public Hittable
{
public:
    virtual Vector hit(const Ray& ray) override;
    void addToWorld(std::shared_ptr<Hittable> const& hittable);

private:
    std::vector<std::shared_ptr<Hittable>> hittables = {};
};
