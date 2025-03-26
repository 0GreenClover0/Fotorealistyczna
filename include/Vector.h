#pragma once

#include <string>

struct Vector
{
    Vector(float x, float y, float z)
        : x(x),
        y(y),
        z(z)
    {
    }

    float x, y, z;

    std::string toString() const;
    Vector operator +(const Vector& v) const;
    Vector operator -(const Vector& v) const;
    bool operator ==(const Vector& v);
    Vector operator *(float f) const;
    Vector operator /(float f) const;
    Vector operator !();          // Negation, way #1
    Vector negative() const;      // Negation, way #2
    float dot(Vector v) const;    // Dot product
    Vector cross(Vector v) const; // Cross product of this x v
    Vector normalized() const;    // Normalize, returns vector of length 1
    float lengthSquared() const;
    float magnitude() const;      // Returns magnitude, length of the vector
    float angle(Vector v) const;  // Returns angle between this vector and the passed vector - IN RADIANS
    static Vector invalid();      // Marks this vector as invalid if you need

};
