#pragma once

#include <iostream>

#include "Vector.h"

class Quaternion
{
public:
    Quaternion(float x, float y, float z, float w);

    float x; // X component of the Quaternion
    
    float y; // Y component of the Quaternion
    
    float z; // Z component of the Quaternion
    
    float w; // W component of the Quaternion

    float& operator[](int index);

    Quaternion operator *(const Quaternion& q) const;
    Quaternion operator +(const Quaternion& q) const;
    Quaternion operator -(const Quaternion& q) const;
    Quaternion operator /(const Quaternion& q) const;
    bool operator==(const Quaternion& q) const;

    static Vector rotate(const Vector& point, const Vector& axis, float angle);

    std::string toString() const;
};
