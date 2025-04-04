#pragma once

#include "Hittable.h"
#include "Vector.h"

class Triangle : public Hittable
{
public:
    Triangle(Vector vertex1, Vector vertex2, Vector vertex3)
    {
        a = vertex1;
        b = vertex2;
        c = vertex3;

        // Winding order
        normal = (b - a).cross(c - a).normalize();
        // normal = (c - a).cross(b - a).normalized();
    }

    virtual void hit(const Ray& ray, HitResult& hitResult) override;

    Vector a = { 0.0f, 0.0f, 0.0f };
    Vector b = { 0.0f, 0.0f, 0.0f };
    Vector c = { 0.0f, 0.0f, 0.0f };
    Vector normal = { 0.0f, 0.0f, 0.0f };
};
