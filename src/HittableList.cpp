#include "HittableList.h"

HitResult HittableList::hit(const Ray& ray)
{
    // TODO: This should be rewritten to HitRecord/HitResult class, implement it later
    HitResult hitResult = {};
    hitResult.hitPoint = Vector::invalid();
    float hitDistanceSquared = FLT_MAX;

    for (auto const& h : hittables)
    {
        HitResult tempHitResult = h->hit(ray);
        float const sqDist = (tempHitResult.hitPoint - ray.origin).lengthSquared();

        if (sqDist < hitDistanceSquared)
        {
            hitResult.material = h->getMaterial();
            hitResult.hitPoint = tempHitResult.hitPoint;
            hitDistanceSquared = sqDist;
        }
    }

    return hitResult;
}

void HittableList::addToWorld(std::shared_ptr<Hittable> const& hittable)
{
    hittables.push_back(hittable);
}