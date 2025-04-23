#include "HittableList.h"

#include <iostream>

#include "MathHelpers.h"

bool HittableList::hit(const Ray& ray, Interval rayT, HitResult& hitResult)
{
    float closestSoFar = rayT.max;
    bool hitAny = false;

    for (auto const& h : hittables)
    {
        HitResult tempHitResult = HitResult();
        h->hit(ray, Interval(rayT.min, closestSoFar), tempHitResult);

        if (tempHitResult.point.isInvalid())
        {
            continue;
        }

        hitResult.hittable = h;
        hitResult.material = tempHitResult.material;
        hitResult.point = tempHitResult.point;
        hitResult.normal = tempHitResult.normal;
        hitResult.frontFace = tempHitResult.frontFace;
        closestSoFar = tempHitResult.t;
        hitAny = true;
    }

    return hitAny;
}

Vector HittableList::getNormal(const Vector& hitPoint) const
{
    // TODO: Implement
    return {};
}

void HittableList::add(std::shared_ptr<Hittable> const& hittable)
{
    hittables.push_back(hittable);
    m_bbox = AABB(m_bbox, hittable->bounding_box());
}
