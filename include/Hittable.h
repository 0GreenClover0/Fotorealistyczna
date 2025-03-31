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

private:
    std::vector<std::shared_ptr<Hittable>> hittables = {};
};
