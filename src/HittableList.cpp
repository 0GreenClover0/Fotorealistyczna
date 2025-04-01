#include "HittableList.h"

#include <iostream>

#include "MathHelpers.h"

HitResult HittableList::hit(const Ray& ray)
{
    // TODO: This should be rewritten to HitRecord/HitResult class, implement it later
    HitResult hitResult = {};
    hitResult.hitPoint = Vector::invalid();
    float hitDistanceSquared = FLT_MAX;

    for (auto const& h : hittables)
    {
        HitResult tempHitResult = h->hit(ray);
        if (!tempHitResult.hitPoint.isInvalid())
        {
            float const sqDist = (tempHitResult.hitPoint - ray.origin).lengthSquared();

            if (tempHitResult.material != nullptr && floatNearlyEqual(tempHitResult.material->color.z, 1.0f) && hitResult.material != nullptr && floatNearlyEqual(hitResult.material->color.x, 1.0f)
                && sqDist < hitDistanceSquared)
            {
                std::cout << ray.origin.toString() << " " << sqDist << " " << hitDistanceSquared << "\n";
            }

            if (sqDist < hitDistanceSquared)
            {
                hitResult.material = h->getMaterial();
                hitResult.hitPoint = tempHitResult.hitPoint;
                hitDistanceSquared = sqDist;
            }
        }
    }

    return hitResult;
}

void HittableList::addToWorld(std::shared_ptr<Hittable> const& hittable)
{
    hittables.push_back(hittable);
}