#include "PointLight.h"

PointLight::PointLight(const Vector& position, const Vector& diffuse, const Vector& specular) : Light(position, diffuse, specular)
{
}

Vector PointLight::getColor(const Ray& rayIn)
{
    return {};
}
