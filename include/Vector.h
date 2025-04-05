#pragma once

#include <random>
#include <string>

struct Vector
{
    Vector(float x, float y, float z)
        : x(x),
        y(y),
        z(z)
    {
    }

    Vector() : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    float x, y, z;

    std::string toString() const;
    std::string toColorString() const;

    Vector operator +(const Vector& v) const;
    Vector operator -(const Vector& v) const;
    Vector operator -() const;
    Vector operator *(const Vector& v) const;
    Vector operator+=(const Vector& vector);
    bool operator ==(const Vector& v) const;
    Vector operator*(float f) const;
    Vector operator /(float f) const;
    Vector operator/(const Vector& v) const;
    Vector operator !() const;          // Negation, way #1
    Vector negative() const;      // Negation, way #2
    float dot(Vector v) const;    // Dot product
    Vector cross(Vector v) const; // Cross product of this x v
    Vector normalize() const;    // Normalize, returns vector of length 1
    float lengthSquared() const;
    float length() const;      // Returns magnitude, length of the vector
    float angle(Vector v) const;  // Returns angle between this vector and the passed vector - IN RADIANS
    static Vector invalid();      // Marks this vector as invalid if you need
    static Vector reflect(const Vector& incident, const Vector& normal);
    static Vector clamp(const Vector& v, float min, float max);
    bool isInvalid() const;
};

inline Vector operator*(float lhs, const Vector& rhs)
{
    return rhs * lhs;
}

static float randomFloat(float const min, float const max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}
