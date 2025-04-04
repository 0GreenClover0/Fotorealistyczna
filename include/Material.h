#pragma once

#include "Vector.h"

class Material
{
public:
    explicit Material(Vector color) : color(color) {}
    Vector color = {};
};
