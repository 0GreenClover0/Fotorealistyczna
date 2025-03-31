#pragma once

#include <vector>

#include "Vector.h"

class Bitmap
{
public:
    Bitmap(int width, int height);

    std::vector<std::vector<Vector>> data = {};
    int width = 0;
    int height = 0;
};
