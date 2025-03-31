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
        Vector ray_start = { 0.0f, 0.0f, -20.0f };
        Ray r1 = { ray_start, sphere_center - ray_start };
        Ray r2 = { ray_start, Vector(0.0f, 1.0f, 0.0f) };

        Vector r3_start = { -10.0f, 0.0f, 10.0f };
        Ray r3 = { r3_start, {0.0f, 0.0f, 1.0f} };

        Vector sphereIntersection1 = intersection(s, r1);
        Vector sphereIntersection2 = intersection(s, r2);
        std::cout << "TEST\n";
        Vector sphereIntersection3 = intersection(s, r3);

        std::cout << "R1 intersects with sphere S at: " + sphereIntersection1.toString() << '\n';
        std::cout << "R2 intersects with sphere S at: " + sphereIntersection2.toString() + " // no intersection" << '\n';
        std::cout << "R3 intersects with sphere S at: " + sphereIntersection3.toString() + " // identical intersections" << '\n';

        Vector normal = Vector(0.0f, 1.0f, 1.0f).normalized();
        Plane p({ 0.0f, 0.0f, 0.0f }, normal);

        Vector v = intersection(r2, p);

        std::cout << "Intersection of plane P and R2: " + v.toString() << '\n';
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
