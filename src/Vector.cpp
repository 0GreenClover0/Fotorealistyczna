#include "Vector.h"

#include "MathHelpers.h"

#include <algorithm>
#include <cmath>
#include <sstream>

std::string Vector::toString() const
{
    if (isnan(x) || isnan(y) || isnan(z))
        return "invalid vector";

    std::stringstream s;
    s << "[" << x << ", " << y << ", " << z << "]";
    return s.str();
}

std::string Vector::toColorString() const
{
    return std::to_string(static_cast<int>(255.999f * x)) + " "
        + std::to_string(static_cast<int>(255.999f * y)) + " "
        + std::to_string(static_cast<int>(255.999f * z)) + '\n';
}

Vector Vector::operator+(const Vector& v) const
{
    return { x + v.x, y + v.y, z + v.z };
}

Vector Vector::operator-(const Vector& v) const
{
    return { x - v.x, y - v.y, z - v.z };
}

Vector Vector::operator-() const
{
    return { -x, -y, -z };
}

Vector Vector::operator*(const Vector& v) const
{
    return { x * v.x, y * v.y, z * v.z };
}

Vector Vector::operator+=(const Vector& vector)
{
    return *this = *this + vector;
}

bool Vector::operator==(const Vector& v) const
{
    return floatNearlyEqual(x, v.x) && floatNearlyEqual(y, v.y) && floatNearlyEqual(z, v.z);
}

Vector Vector::operator*(float f) const
{
    return { x * f, y * f, z * f };
}

Vector Vector::operator/(float f) const
{
    return { x / f, y / f, z / f };
}

Vector Vector::operator/(const Vector& v) const
{
    return { x / v.x, y / v.y, z / v.z };
}

Vector Vector::operator!() const
{
    return negative();
}

Vector Vector::negative() const
{
    return { -x, -y, -z };
}

float Vector::dot(Vector v) const
{
    return x * v.x + y * v.y + z * v.z;
}

Vector Vector::cross(Vector v) const
{
    return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x };
}

Vector Vector::normalize() const
{
    return *this / length();
}

float Vector::lengthSquared() const
{
    return x * x + y * y + z * z;
}

float Vector::length() const
{
    return sqrt(lengthSquared());
}

float Vector::angle(Vector v) const
{
    return acos(dot(v) / (length() * v.length()));
}

Vector Vector::invalid()
{
    return { NAN, NAN, NAN };
}

Vector Vector::reflect(const Vector& incident, const Vector& normal)
{
    return incident - 2.0f * normal * incident.dot(normal);
}

Vector Vector::refract(const Vector& uv, const Vector& n, float etai_over_etat)
{
    float cos_theta = std::fmin((-uv).dot(n), 1.0f);
    Vector r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vector r_out_parallel = -std::sqrt(std::fabs(1.0f - r_out_perp.lengthSquared())) * n;
    return r_out_perp + r_out_parallel;
}

Vector Vector::clamp(const Vector& v, float min, float max)
{
    return Vector(std::clamp(v.x, min, max), std::clamp(v.y, min, max), std::clamp(v.z, min, max));
}

bool Vector::isInvalid() const
{
    return isnan(x) || isnan(y) || isnan(z);
}

bool Vector::nearZero() const
{
    float constexpr epsilon = 1e-7f;
    return std::fabs(x) < epsilon && std::fabs(y) < epsilon && std::fabs(z) < epsilon;
}

Vector Vector::random_in_unit_sphere()
{
    while (true)
    {
        Vector p = Vector(randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f), randomFloat(-1.0f, 1.0f));

        if (p.lengthSquared() < 1.0f)
        {
            return p;
        }
    }
}

Vector Vector::random_unit_vector()
{
    return random_in_unit_sphere().normalize();
}
