#pragma once

#include "Interval.h"
#include "Ray.h"
#include "Vector.h"

class Hittable;
class Material;

struct HitResult
{
    HitResult() : point(Vector::invalid())
    {
    }

    Vector point = {};
    Vector normal = {};
    std::shared_ptr<Hittable> hittable = {};
    std::shared_ptr<Material> material = {};
    float t = {};
    bool frontFace = false;

    void setFaceNormal(const Ray& ray, const Vector& outwardNormal)
    {
        frontFace = ray.direction.dot(outwardNormal) < 0.0f;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
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
