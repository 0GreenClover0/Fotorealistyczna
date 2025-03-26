#include "Quaternion.h"
#include <complex.h>
#include <sstream>

#include "Vector.h"

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}

float& Quaternion::operator[](int index)
{
    switch (index)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default:
            throw std::invalid_argument("Invalid Quaternion index!");
    }
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
    /*return {
        this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
        this->w * q.y + this->y * q.w + this->z * q.x - this->x * q.z,
        this->w * q.z + this->z * q.w + this->x * q.y - this->y * q.x,
        this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z
    };*/

    const auto first_vector = Vector(this->x, this->y, this->z);
    const auto second_vector = Vector(q.x, q.y, q.z);

    float result_w = this->w * q.w - Vector(first_vector).dot(second_vector);
    Vector result_vector = second_vector * this->w + first_vector * q.w + first_vector.cross(second_vector);

    return { result_vector.x, result_vector.y, result_vector.z, result_w };
}

Quaternion Quaternion::operator/(const Quaternion& q) const
{
    const auto first_vector = Vector(this->x, this->y, this->z);
    const auto second_vector = Vector(q.x, q.y, q.z);

    const float divided_by = q.w * q.w + second_vector.dot(second_vector);
    float result_w = (this->w * q.w + Vector(first_vector).dot(second_vector)) / (divided_by);
    Vector result_vector = (second_vector * -this->w + first_vector * q.w - first_vector.cross(second_vector)) * (1.0f / (divided_by));

    return { result_vector.x, result_vector.y, result_vector.z, result_w };
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
    return {
        this->x + q.x,
        this->y + q.y,
        this->z + q.z,
        this->w + q.w
    };
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
    return {
        this->x - q.x,
        this->y - q.y,
        this->z - q.z,
        this->w - q.w
    };
}

bool Quaternion::operator==(const Quaternion& q) const
{
    return this->w == q.w && this->x == q.x && this->y == q.y && this->z == q.z;
}

Vector Quaternion::rotate(const Vector& point, const Vector& axis, float angle)
{
    const Vector result_vector = axis.normalized() * std::sin(angle / 2.0f);
    const float result_w = std::cos(angle / 2.0f);
    Quaternion q = Quaternion(result_vector.x, result_vector.y, result_vector.z, result_w);
    Quaternion q_inverted = Quaternion(-result_vector.x, -result_vector.y, -result_vector.z, result_w);

    Quaternion point_quaternion = Quaternion(point.x, point.y, point.z, 0.0f);
    Quaternion result = q * point_quaternion * q_inverted;
    return { result.x, result.y, result.z };
}

std::string Quaternion::toString() const
{
    std::stringstream s{};
    s << "(";
    s << x;
    s << "i, ";
    s << y;
    s << "j, ";
    s << z;
    s << "k, ";
    s << w;
    s << ")";
    return s.str();
}
