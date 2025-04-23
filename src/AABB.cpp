#include "AABB.h"

#include <algorithm>

AABB const AABB::empty = AABB(Interval::empty, Interval::empty, Interval::empty);
AABB const AABB::whole = AABB(Interval::whole, Interval::whole, Interval::whole);

AABB::AABB(const AABB& box0, const AABB& box1)
{
    x = Interval(box0.x, box1.x);
    y = Interval(box0.y, box1.y);
    z = Interval(box0.z, box1.z);
}

AABB::AABB(const Interval& x, const Interval& y, const Interval& z) : x(x), y(y), z(z)
{
    pad_to_minimums();
}

AABB::AABB(const Vector& a, const Vector& b)
{
    x = a.x <= b.x ? Interval(a.x, b.x) : Interval(b.x, a.x);
    y = a.y <= b.y ? Interval(a.y, b.y) : Interval(b.y, a.y);
    z = a.z <= b.z ? Interval(a.z, b.z) : Interval(b.z, a.z);

    pad_to_minimums();
}

Interval const& AABB::axis_interval(const int n) const
{
    if (n == 1)
    {
        return y;
    }

    if (n == 2)
    {
        return z;
    }

    return x;
}

bool AABB::hit(const Ray& ray, Interval ray_t) const
{
    const Vector& ray_origin = ray.origin;
    const Vector& ray_direction = ray.direction;

    for (int axis = 0; axis < 3; ++axis)
    {
        Interval const& ax = axis_interval(axis);
        float const adinv = 1.0f / ray_direction[axis];

        float const t0 = (ax.min - ray_origin[axis]) * adinv;
        float const t1 = (ax.max - ray_origin[axis]) * adinv;

        if (t0 < t1)
        {
            ray_t.min = std::max(t0, ray_t.min);

            ray_t.max = std::min(t1, ray_t.max);
        }
        else
        {
            ray_t.min = std::max(t1, ray_t.min);

            ray_t.max = std::min(t0, ray_t.max);
        }

        if (ray_t.max <= ray_t.min)
        {
            return false;
        }
    }

    return true;
}


// Returns the index of the longest axis of the bounding box.
int AABB::longest_axis() const
{
    if (x.size() > y.size())
    {
        return x.size() > z.size() ? 0 : 2;
    }

    return y.size() > z.size() ? 1 : 2;
}

void AABB::pad_to_minimums()
{
    // Adjust the AABB so that no side is narrower than some delta, padding if necessary.
    float constexpr delta = 0.0001f;

    if (x.size() < delta)
        x = x.expand(delta);

    if (y.size() < delta)
        y = y.expand(delta);

    if (z.size() < delta)
        z = z.expand(delta);
}
