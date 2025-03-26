#include <iostream>

#include "Line.h"
#include "MathHelpers.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"

int main()
{
    {
        Vector a = { 1.0f, 2.0f, 3.0f };
        Vector b = { 2.0f, 4.0f, 8.0f };

        if (a + b == b + a)
            std::cout << "Addition commutative: SUCCESS";
        else
            std::cout << "Addition commutative: FAIL";

        std::cout << std::endl;
    }

    {
        Vector a = { 0.0f, 3.0f, 0.0f };
        Vector b = { 5.0f, 5.0f, 0.0f };

        std::cout << a.angle(b) * 180 / PI << " deg" << std::endl;
    }

    {
        Vector a = { 4.0f, 5.0f, 1.0f };
        Vector b = { 4.0f, 1.0f, 3.0f };
        Vector c = a.cross(b);
        std::cout << a.toString() + " CROSS " + b.toString() + " = " + c.toString() << std::endl;
        std::cout << c.toString() + ".normalized() = " + c.normalized().toString() << std::endl;
    }

    {
        Vector sphere_center = { 0.0f, 0.0f, 0.0f };
        Sphere s = { sphere_center, 10.0f };
        Vector ray_start = { 0.0f, 0.0f, 20.0f };
        Ray r1 = { sphere_center, sphere_center - ray_start };
        Ray r2 = { sphere_center, Vector(0.0f, 1.0f, 0.0f) };

        Vector r3_start = { -10.0f, 0.0f, 10.0f };
        Ray r3 = { sphere_center, {0.0f, 0.0f, 1.0f} };

        auto pair1 = intersection(s, r1);
        auto pair2 = intersection(s, r2);
        auto pair3 = intersection(s, r3);

        std::cout << "R1 intersects with sphere S at: " + pair1.first.toString() + ", " + pair1.second.toString() << std::endl;
        std::cout << "R2 intersects with sphere S at: " + pair2.first.toString() + ", " + pair2.second.toString() + " // no intersection" << std::endl;
        std::cout << "R3 intersects with sphere S at: " + pair3.first.toString() + ", " + pair3.second.toString() + " // identical vectors, one intersection" << std::endl;

        Vector normal = Vector(0.0f, 1.0f, 1.0f).normalized();
        Plane p({ 0.0f, 0.0f, 0.0f }, normal);

        Vector v = intersection(r2, p);

        std::cout << "Intersection of plane P and R2: " + v.toString() << std::endl;
    }

    // Right-handed system, CCW triangles, as in OpenGL
    Triangle t({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });

    {
        Vector p1(-1.0f, 0.5f, 0.0f);
        Vector p2(1.0f, 0.5f, 0.0f);
        Ray r(p1, p2 - p1);

        Vector v = intersection(r, t);

        std::cout << "Intersection of ray R and triangle T: " + v.toString() << std::endl; // Coplanar, no intersection in our implementation
    }

    {
        Vector p1(2.0f, -1.0f, 0.0f);
        Vector p2(2.0f, 1.0f, 0.0f);
        Ray r(p1, p2 - p1);

        Vector v = intersection(r, t);

        std::cout << "Intersection of ray R and triangle T: " + v.toString() << std::endl; // Coplanar AND no intersection
    }

    {
        Vector p1(0.0f, 0.0f, -1.0f);
        Vector p2(0.0f, 0.0f, 1.0f);
        Ray r(p1, p2 - p1);

        Vector v = intersection(r, t);

        std::cout << "Intersection of ray R and triangle T: " + v.toString() << std::endl;
    }

    {
        Vector p1(0.0f, 0.0f, 0.4f);
        Vector p2(0.3f, 0.3f, -0.4f);
        Ray r(p1, p2 - p1);

        Vector v = intersection(r, t);

        std::cout << "Extra intersection of ray R and triangle T: " + v.toString() << std::endl;
    }
}
