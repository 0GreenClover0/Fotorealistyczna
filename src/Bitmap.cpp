#include "Bitmap.h"

Bitmap::Bitmap(int width, int height) : width(width), height(height)
{
    data.resize(height);

    for (int i = 0; i < height; i++)
    {
        data[i].resize(width);
    }
}
