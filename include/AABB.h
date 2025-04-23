#pragma once

#include "Interval.h"
#include "Ray.h"

struct AABB
{
    Interval x;
    Interval y;
    Interval z;

    AABB() = default;

    AABB(const AABB& box0, const AABB& box1);

    AABB(const Interval& x, const Interval& y, const Interval& z);

    AABB(const Vector& a, const Vector& b);

    [[nodiscard]] const Interval& axis_interval(const int n) const;

    [[nodiscard]] bool hit(const Ray& ray, Interval ray_t) const;

    [[nodiscard]] int longest_axis() const;

    static const AABB empty;
    static const AABB whole;

private:
    void pad_to_minimums();
};

inline AABB operator+(AABB const& bbox, Vector const& offset)
{
    return AABB(bbox.x + offset.x, bbox.y + offset.y, bbox.z + offset.z);
}

inline AABB operator*(AABB const& bbox, Vector const& scale)
{
    return AABB(bbox.x * scale.x, bbox.y * scale.y, bbox.z * scale.z);
}

inline AABB operator+(Vector const& offset, AABB const& bbox)
{
    return bbox + offset;
}
