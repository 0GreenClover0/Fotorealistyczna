#include "Plane.h"
#include "MathHelpers.h"

Plane::Plane(const Vector& p, const Vector& normal, std::shared_ptr<Material> const& mat)
{
    this->p = p;
    this->normal = normal;
    this->material = mat;
}

void Plane::hit(const Ray& ray, Interval rayT, HitResult& hitResult)
{
    float const denom = normal.dot(ray.direction);
    if (floatNearlyEqual(denom, 0.0f))
    {
        return; // Ray is parallel to plane
    }

    float const t = (p - ray.origin).dot(normal) / denom;

    if (!rayT.contains(t))
    {
        return;
    }

    hitResult.t = t;
    hitResult.hitPoint = ray.origin + ray.direction * t;
}

Vector Plane::getNormal(const Vector& hitPoint) const
{
    return normal;
}
