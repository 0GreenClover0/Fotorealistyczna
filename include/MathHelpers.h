#pragma once

#define PI 3.14159265359f

#include "Line.h"
#include "Plane.h"
#include "Ray.h"
#include "Vector.h"
#include "Sphere.h"
#include "Triangle.h"

#include <cmath>
#include <iostream>

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

    const float t1 = (((p2 - p1).cross(v2)).dot(v1.cross(v2))) / std::pow((v1.cross(v2)).length(), 2);
    const float t2 = -(((p2 - p1).cross(v1)).dot(v2.cross(v1))) / std::pow((v2.cross(v1)).length(), 2);

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

inline Vector intersection(const Ray& ray, const Plane& plane)
{
    Vector normal = plane.normal;
    Vector ray_origin = ray.origin;
    Vector plane_point = plane.p;
    Vector ray_direction = ray.direction;

    float denominator = normal.dot(ray_direction);

    // Check if ray is parallel to the plane
    if (std::fabs(denominator) < 1e-6f)
    {
        return Vector::invalid();
    }

    float distance = normal.dot(plane_point - ray_origin) / denominator;

    if (distance < 0.0f)
    {
        return Vector::invalid();
    }

    return ray_origin + ray_direction * distance;
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
    float b = 2.0f * l.v.dot((l.p - s.center));
    float c = (l.p - s.center).dot(l.p - s.center) - (s.radius * s.radius);

    float delta = b * b - 4.0f * a * c;

    if (delta < 0)
        return std::make_pair(Vector::invalid(), Vector::invalid());

    float t1 = (-b + sqrt(delta)) / (2.0f * a);
    float t2 = (-b - sqrt(delta)) / (2.0f * a);

    Vector p1 = l.p + l.v * t1;
    Vector p2 = l.p + l.v * t2;

    return std::make_pair<Vector, Vector>(Vector(p1), Vector(p2));
}

static float radians(const float degrees)
{
    return degrees * (PI / 180.0f);
}

static float degrees(const float radians)
{
    return radians * (180.0f / PI);
}

inline Vector intersection(Ray l1, Ray l2)
{
    const Vector p1 = l1.origin;
    const Vector p2 = l2.origin;
    const Vector v1 = l1.direction;
    const Vector v2 = l2.direction;

    const float t1 = (((p2 - p1).cross(v2)).dot(v1.cross(v2))) / std::pow((v1.cross(v2)).length(), 2);
    const float t2 = -(((p2 - p1).cross(v1)).dot(v2.cross(v1))) / std::pow((v2.cross(v1)).length(), 2);

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
    float det = direction.length() * direction.length();

    if (det == 0.0f)
        return Line({ 0,0,0 }, Vector::invalid());

    Vector point = ((direction.cross(p2.normal) * p1.d) + (p1.normal.cross(direction) * p2.d)) / det;

    return Line(point, direction);
}

inline Vector intersection(Ray r, Triangle triangle)
{
    Vector normal = triangle.normal;
    float dot = normal.dot(r.direction);

    // The ray and the triangle are coplanar. We treat it as NO intersection
    if (floatNearlyEqual(dot, 0.0f))
        return Vector::invalid();

    Vector ra = triangle.a - r.origin;
    float t = triangle.normal.dot(ra) / dot;

    if (t < 0.0f && !floatNearlyEqual(dot, 0.0f))
        return Vector::invalid();

    Vector intersectionPoint = r.origin + r.direction * t;

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

