#include "HittableList.h"

#include <iostream>

#include "MathHelpers.h"

void HittableList::hit(const Ray& ray, Interval rayT, HitResult& hitResult)
{
    float closestSoFar = rayT.max;

    for (auto const& h : hittables)
    {
        HitResult tempHitResult = {.hittable= nullptr, .hitPoint= Vector::invalid(), .t= 0.0f};
        h->hit(ray, Interval(rayT.min, closestSoFar), tempHitResult);

        if (tempHitResult.hitPoint.isInvalid())
        {
            continue;
        }

        hitResult.hittable = h;
        hitResult.hitPoint = tempHitResult.hitPoint;
        closestSoFar = tempHitResult.t;
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
