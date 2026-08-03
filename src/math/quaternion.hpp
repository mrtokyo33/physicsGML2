#pragma once

#include "vector.hpp"
#include "matrix3x3.hpp"

class Quaternion {
public:
    double w;
    double x;
    double y;
    double z;

    Quaternion();

    Quaternion(
        double w,
        double x,
        double y,
        double z
    );

    static Quaternion identity();

    double magnitude() const;
    double magnitudeSquared() const;

    Quaternion normalized() const;
    Quaternion conjugate() const;
    Quaternion inverse() const;

    Matrix3x3 toMatrix() const;

    Quaternion operator+(const Quaternion& other) const;
    Quaternion operator-(const Quaternion& other) const;

    Quaternion operator*(double scalar) const;
    Quaternion operator/(double scalar) const;

    Quaternion operator*(const Quaternion& other) const;

    Vector3D rotate(const Vector3D& vector) const;
};