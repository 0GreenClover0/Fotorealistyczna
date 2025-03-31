#include "Vector.h"

#include "MathHelpers.h"

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

Vector Vector::operator+(const Vector& v) const
{
    return { x + v.x, y + v.y, z + v.z };
}

Vector Vector::operator-(const Vector& v) const
{
    return { x - v.x, y - v.y, z - v.z };
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

Vector Vector::normalized() const
{
    return *this / magnitude();
}

float Vector::lengthSquared() const
{
    return x * x + y * y + z * z;
}

float Vector::magnitude() const
{
    return sqrt(lengthSquared());
}

float Vector::angle(Vector v) const
{
    return acos(dot(v) / (magnitude() * v.magnitude()));
}

Vector Vector::invalid()
{
    return { NAN, NAN, NAN };
}
