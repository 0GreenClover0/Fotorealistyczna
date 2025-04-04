#include "HittableList.h"

#include <iostream>

#include "MathHelpers.h"

void HittableList::hit(const Ray& ray, HitResult& hitResult)
{
    float hitDistanceSquared = FLT_MAX;

    for (auto const& h : hittables)
    {
        HitResult tempHitResult = {nullptr, Vector::invalid()};
        h->hit(ray, tempHitResult);

        if (tempHitResult.hitPoint.isInvalid())
        {
            continue;
        }

        float const sqDist = (tempHitResult.hitPoint - ray.origin).lengthSquared();

        if (sqDist < hitDistanceSquared)
        {
            hitResult.hittable = h;
            hitResult.hitPoint = tempHitResult.hitPoint;
            hitDistanceSquared = sqDist;
        }
    }
}

Vector HittableList::getNormal(const Vector& hitPoint) const
{
    // TODO: Implement
    return {};
}

void HittableList::addToWorld(std::shared_ptr<Hittable> const& hittable)
{
    hittables.push_back(hittable);
}
