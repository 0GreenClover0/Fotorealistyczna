#pragma once
#include "Vector.h"

class Triangle
{
public:

    Triangle(Vector vertex1, Vector vertex2, Vector vertex3)
    {
        a = vertex1;
        b = vertex2;
        c = vertex3;

        // Winding order
        normal = (b - a).cross(c - a).normalized();
        // normal = (c - a).cross(b - a).normalized();
    }

    Vector a = { 0.0f, 0.0f, 0.0f };
    Vector b = { 0.0f, 0.0f, 0.0f };
    Vector c = { 0.0f, 0.0f, 0.0f };
    Vector normal = { 0.0f, 0.0f, 0.0f };
};
