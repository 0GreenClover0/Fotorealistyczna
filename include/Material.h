#pragma once
#include "Vector.h"

class Material
{
public:
    Material(Vector materialColor) : color(materialColor) {}
    Vector color = {};
};
