#pragma once

#include "Hittable.h"
#include "Vector.h"

class Triangle : public Hittable
{
public:
    Triangle(Vector vertex1, Vector vertex2, Vector vertex3, std::shared_ptr<Material> const& mat)
    {
        a = vertex1;
        b = vertex2;
        c = vertex3;

        edge0 = b - a;
        edge1 = c - b;
        edge2 = a - c;

        // Winding order
        normal = (b - a).cross(c - a).normalize();
        //normal = (c - a).cross(b - a).normalize();

        material = mat;
    }

    virtual void hit(const Ray& ray, Interval rayT, HitResult& hitResult) override;
    virtual Vector getNormal(const Vector& hitPoint) const override;

    Vector a = { 0.0f, 0.0f, 0.0f };
    Vector b = { 0.0f, 0.0f, 0.0f };
    Vector c = { 0.0f, 0.0f, 0.0f };
    Vector normal = { 0.0f, 0.0f, 0.0f };

private:
    Vector edge0;
    Vector edge1;
    Vector edge2;
};
