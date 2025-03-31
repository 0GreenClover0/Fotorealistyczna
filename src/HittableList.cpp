#include "HittableList.h"

Vector HittableList::hit(const Ray& ray)
{
    // TODO: This should be rewritten to HitRecord/HitResult class, implement it later
    Vector hitResult = Vector::invalid();
    float hitDistanceSquared = FLT_MAX;

    for (auto const& h : hittables)
    {
        Vector tempHitResult = h->hit(ray);
        float const sqDist = (tempHitResult - ray.origin).lengthSquared();

        if (sqDist < hitDistanceSquared)
        {
            hitResult = tempHitResult;
            hitDistanceSquared = sqDist;
        }
    }

    return hitResult;
}

void HittableList::addToWorld(std::shared_ptr<Hittable> const& hittable)
{
    hittables.push_back(hittable);
}