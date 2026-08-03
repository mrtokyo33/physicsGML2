#include "vector.hpp"

#include <cmath>
#include <stdexcept>

double Vector3D::magnitude() const {
    return std::sqrt(magnitudeSquared());
}

double Vector3D::magnitudeSquared() const {
    return x * x + y * y + z * z;
}

Vector3D Vector3D::normalized() const {
    const double mag = magnitude();
    if (mag == 0.0) {
        return Vector3D{0.0, 0.0, 0.0};
    }

    return Vector3D{
        x / mag,
        y / mag,
        z / mag
    };
}

double Vector3D::dot(const Vector3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D& other) const {
    return Vector3D{
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D{
        x + other.x,
        y + other.y,
        z + other.z
    };
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    return Vector3D{
        x - other.x,
        y - other.y,
        z - other.z
    };
}

Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D{
        x * scalar,
        y * scalar,
        z * scalar
    };
}

Vector3D Vector3D::operator/(double scalar) const {
    if (scalar == 0.0) {
        throw std::invalid_argument("Division by zero");
    }

    return Vector3D{
        x / scalar,
        y / scalar,
        z / scalar
    };
}
