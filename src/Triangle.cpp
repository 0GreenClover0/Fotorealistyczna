#include "Triangle.h"

#include "MathHelpers.h"

bool Triangle::hit(const Ray& ray, Interval rayT, HitResult& hitResult)
{
    Vector normal = this->normal;
    float dot = normal.dot(ray.direction);

    // The ray and the triangle are coplanar. We treat it as NO intersection
    if (floatNearlyEqual(dot, 0.0f))
        return false;

    Vector ra = a - ray.origin;
    float t = normal.dot(ra) / dot;

    if (!rayT.surrounds(t))
        return false;

    Vector intersectionPoint = ray.origin + ray.direction * t;

    Vector c0 = (a - intersectionPoint).cross(edge0);
    Vector c1 = (b - intersectionPoint).cross(edge1);
    Vector c2 = (c - intersectionPoint).cross(edge2);

    if (c0.dot(normal) >= 0 && c1.dot(normal) >= 0 && c2.dot(normal) >= 0)
    {
        hitResult.material = material;
        hitResult.point = intersectionPoint;
        hitResult.t = t;
        hitResult.setFaceNormal(ray, normal);
        return true;
    }

    return false;
}

Vector Triangle::getNormal(const Vector& hitPoint) const
{
    return {};
}
