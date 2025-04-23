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

        // m_q = a
        // m_u = b - a
        // m_v = c - a
        // a, a + b - a + c - a = b + c - a
        // a + b - a = b, a + c - a = c

        auto const bbox_diagonal1 = AABB(a, b + c - a);
        auto const bbox_diagonal2 = AABB(b, c);
        m_bbox = AABB(bbox_diagonal1, bbox_diagonal2);
    }

    virtual bool hit(const Ray& ray, Interval rayT, HitResult& hitResult) override;
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
