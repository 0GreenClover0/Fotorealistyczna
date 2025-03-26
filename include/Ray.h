#pragma once

#include "Line.h"

class Ray : public Line
{
public:
    // p - start, v - end
    Ray(const Vector& p, const Vector& v) : Line(p, v) {}
};
