#pragma once

#include "Light.h"
#include "Ray.h"

class PointLight : public Light
{
public:
    PointLight(const Vector& position, const Vector& diffuse, const Vector& specular);

    Vector getColor(const Ray& rayIn);
};
