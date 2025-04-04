#pragma once

#include "Light.h"
#include "Ray.h"

class PointLight : public Light
{
public:
    PointLight(const Vector& position, const Vector& color, const float intensity);

    Vector getColor(const Ray& rayIn);
};
