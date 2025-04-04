#include "PointLight.h"

PointLight::PointLight(const Vector& position, const Vector& color, const float intensity) : Light(position, color, intensity)
{
}

Vector PointLight::getColor(const Ray& rayIn)
{
    return {};
}
