#include "Plane.h"

#include "MathHelpers.h"

Plane::Plane(const Vector& p, const Vector& normal)
{
    this->p = p;
    this->normal = normal;
}

Plane::Plane(float a, float b, float c, float d)
{
    this->normal = { a, b, c };
    this->d = d;
    p = { 0, 0, -d / c };

    if (floatNearlyEqual(this->normal.angle({ 0,0,1 }) * 180 / PI, 0))
        p = { 0, -d / b, 0 };
    if (floatNearlyEqual(this->normal.angle({ 0,1,0 }) * 180 / PI, 0))
        p = { -d / a, 0, 0 };
}

HitResult Plane::hit(const Ray& ray)
{
    return {};
}
