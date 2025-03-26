#pragma once
#include <iostream>
#define PI 3.14159265f
#include "Line.h"
#include "Plane.h"
#include "Ray.h"
#include "Vector.h"
#include "Sphere.h"
#include "Triangle.h"

enum Axis
{
    X,
    Y,
    Z
};

inline bool floatNearlyEqual(float d1, float d2, float tolerance = 0.000001f)
{
    return (std::abs(d1 - d2) < tolerance);
}

inline Vector intersection(Line l1, Line l2)
{
    const Vector p1 = l1.p;
    const Vector p2 = l2.p;
    const Vector v1 = l1.v;
    const Vector v2 = l2.v;

    const float t1 = (((p2 - p1).cross(v2)).dot(v1.cross(v2))) / std::pow((v1.cross(v2)).magnitude(), 2);
    const float t2 = -(((p2 - p1).cross(v1)).dot(v2.cross(v1))) / std::pow((v2.cross(v1)).magnitude(), 2);

    if (p1 + v1 * t1 == p2 + v2 * t2)
        return p1 + v1 * t1;

    return Vector::invalid();
}

inline float angleBetween(Line l1, Line l2)
{
    Vector v1 = l1.v;
    Vector v2 = l2.v;
    return v1.angle(v2);
}

inline Vector intersection(Line l, Plane p)
{
    Vector n = p.normal;
    Vector p0 = l.p;
    Vector q0 = p.p;
    Vector v = l.v;

    float t = -n.dot(p0 - q0) / n.dot(v);
    Vector P = p0 + v * t;

    if (n.dot(P - q0) == 0)
        return P;

    return Vector::invalid();
}

inline float angleBetween(Line l, Plane p)
{
    const Vector n = p.normal;
    const Vector v = l.v;
    const float angleDeg = v.angle(n) * 180 / PI;
    float result = 0;

    if (angleDeg > 90)
        result = angleDeg - 90;
    else
        result = 90 - angleDeg;

    return result;
}

inline std::pair<Vector, Vector> intersection(Sphere s, Line l)
{
    float a = l.v.dot(l.v);
    float b = 2.0f * l.v.dot((l.p - s.point));
    float c = (l.p - s.point).dot(l.p - s.point) - (s.radius * s.radius);

    float delta = b * b - 4.0f * a * c;

    if (delta < 0)
        return std::make_pair(Vector::invalid(), Vector::invalid());

    float t1 = (-b + sqrt(delta)) / (2.0f * a);
    float t2 = (-b - sqrt(delta)) / (2.0f * a);

    Vector p1 = l.p + l.v * t1;
    Vector p2 = l.p + l.v * t2;

    return std::make_pair<Vector, Vector>(Vector(p1), Vector(p2));
}

inline std::pair<Vector, Vector> intersection(Sphere s, Ray const& ray)
{
    float a = ray.v.lengthSquared();
    float h = ray.v.dot(s.point);
    float c = s.point.lengthSquared() - s.radius * s.radius;

    float discriminant = h * h - a * c;
    if (floatNearlyEqual(discriminant, 0.0f))
    {
        return std::make_pair(Vector::invalid(), Vector::invalid());
    }

    float sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = (h - sqrtd) / a;

    if (root < 0.0f)
    {
        root = (h + sqrtd) / a;
        Vector p = ray.p + ray.v * root;
        return std::make_pair(p, Vector::invalid());
    }
    else
    {
        root = (h + sqrtd) / a;

        if (root > 0.0f)
        {
            return std::make_pair(Vector::invalid(), Vector::invalid());
        }
    }

    float root2 = (h - sqrtd) / a;
    float root3 = (h + sqrtd) / a;

    //Vector p = ray.p + ray.v * root;
    Vector p2 = ray.p + ray.v * root2;
    Vector p3 = ray.p + ray.v * root3;

    return std::make_pair(p2, p3);
}

inline Vector intersection(Ray l1, Ray l2)
{
    const Vector p1 = l1.p;
    const Vector p2 = l2.p;
    const Vector v1 = l1.v;
    const Vector v2 = l2.v;

    const float t1 = (((p2 - p1).cross(v2)).dot(v1.cross(v2))) / std::pow((v1.cross(v2)).magnitude(), 2);
    const float t2 = -(((p2 - p1).cross(v1)).dot(v2.cross(v1))) / std::pow((v2.cross(v1)).magnitude(), 2);

    if (t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1)
        return Vector::invalid();

    if (p1 + v1 * t1 == p2 + v2 * t2)
        return p1 + v1 * t1;

    return Vector::invalid();
}

inline Line intersection(Plane p1, Plane p2)
{
    if (p1.normal.angle(p2.normal) == 0 && p1.p == p2.p) // If planes are equal this returns example vector from them
        return Line(p1.p, (Vector(0, 1, 0).cross(p1.normal)));

    Vector direction = p1.normal.cross(p2.normal);
    float det = direction.magnitude() * direction.magnitude();

    if (det == 0.0f)
        return Line({ 0,0,0 }, Vector::invalid());

    Vector point = ((direction.cross(p2.normal) * p1.d) + (p1.normal.cross(direction) * p2.d)) / det;

    return Line(point, direction);
}

inline Vector intersection(Ray r, Triangle triangle)
{
    Vector normal = triangle.normal;
    float dot = normal.dot(r.v);

    // The ray and the triangle are coplanar. We treat it as NO intersection
    if (floatNearlyEqual(dot, 0.0f))
        return Vector::invalid();

    Vector ra = triangle.a - r.p;
    float t = triangle.normal.dot(ra) / dot;

    if (t < 0.0f && !floatNearlyEqual(dot, 0.0f))
        return Vector::invalid();

    Vector intersectionPoint = r.p + r.v * t;

    Vector edge0 = triangle.b - triangle.a;
    Vector edge1 = triangle.c - triangle.b;
    Vector edge2 = triangle.a - triangle.c;
    Vector c0 = (triangle.a - intersectionPoint).cross(edge0);
    Vector c1 = (triangle.b - intersectionPoint).cross(edge1);
    Vector c2 = (triangle.c - intersectionPoint).cross(edge2);

    if (c0.dot(normal) >= 0 && c1.dot(normal) >= 0 && c2.dot(normal) >= 0)
    {
        return intersectionPoint;
    }

    return Vector::invalid();
}

inline float angleBetween(Plane p1, Plane p2)
{
    return p1.normal.angle(p2.normal);
}

