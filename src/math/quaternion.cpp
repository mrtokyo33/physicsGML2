#include "quaternion.hpp"

#include <cmath>

Quaternion::Quaternion()
    : w(1.0),
      x(0.0),
      y(0.0),
      z(0.0)
{
}

Quaternion::Quaternion(
    double w,
    double x,
    double y,
    double z
)
    : w(w),
      x(x),
      y(y),
      z(z)
{
}

Quaternion Quaternion::identity() {
    return Quaternion{1.0, 0.0, 0.0, 0.0};
}

double Quaternion::magnitudeSquared() const {
    return w*w + x*x + y*y + z*z;
}

double Quaternion::magnitude() const {
    return std::sqrt(magnitudeSquared());
}

Quaternion Quaternion::normalized() const {

    double mag = magnitude();

    if (mag == 0.0)
        return Quaternion();

    return Quaternion{
        w / mag,
        x / mag,
        y / mag,
        z / mag
    };
}

Quaternion Quaternion::conjugate() const {

    return Quaternion{
        w,
        -x,
        -y,
        -z
    };
}

Quaternion Quaternion::inverse() const {

    double mag2 = magnitudeSquared();

    if (mag2 == 0.0)
        return Quaternion();

    return conjugate() / mag2;
}

Quaternion Quaternion::operator+(const Quaternion& other) const {

    return Quaternion{
        w + other.w,
        x + other.x,
        y + other.y,
        z + other.z
    };
}

Quaternion Quaternion::operator-(const Quaternion& other) const {

    return Quaternion{
        w - other.w,
        x - other.x,
        y - other.y,
        z - other.z
    };
}

Quaternion Quaternion::operator*(double scalar) const {

    return Quaternion{
        w * scalar,
        x * scalar,
        y * scalar,
        z * scalar
    };
}

Quaternion Quaternion::operator/(double scalar) const {

    return Quaternion{
        w / scalar,
        x / scalar,
        y / scalar,
        z / scalar
    };
}

Quaternion Quaternion::operator*(const Quaternion& other) const {

    return Quaternion{

        w * other.w - x * other.x - y * other.y - z * other.z,

        w * other.x + x * other.w + y * other.z - z * other.y,

        w * other.y - x * other.z + y * other.w + z * other.x,

        w * other.z + x * other.y - y * other.x + z * other.w
    };
}

Vector3D Quaternion::rotate(const Vector3D& vector) const {

    Quaternion qv{
        0.0,
        vector.x,
        vector.y,
        vector.z
    };

    Quaternion result = (*this) * qv * inverse();

    return Vector3D{
        result.x,
        result.y,
        result.z
    };
}

Matrix3x3 Quaternion::toMatrix() const {

    Quaternion q = normalized();

    double xx = q.x * q.x;
    double yy = q.y * q.y;
    double zz = q.z * q.z;

    double xy = q.x * q.y;
    double xz = q.x * q.z;
    double yz = q.y * q.z;

    double wx = q.w * q.x;
    double wy = q.w * q.y;
    double wz = q.w * q.z;

    return Matrix3x3{

        1.0 - 2.0 * (yy + zz),
        2.0 * (xy - wz),
        2.0 * (xz + wy),

        2.0 * (xy + wz),
        1.0 - 2.0 * (xx + zz),
        2.0 * (yz - wx),

        2.0 * (xz - wy),
        2.0 * (yz + wx),
        1.0 - 2.0 * (xx + yy)
    };
}