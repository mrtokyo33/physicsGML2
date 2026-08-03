#pragma once

#include "vector.hpp"

class Matrix3x3 {
public:
    double m[3][3];

    Matrix3x3();

    Matrix3x3(
        double m00, double m01, double m02,
        double m10, double m11, double m12,
        double m20, double m21, double m22
    );

    static Matrix3x3 identity();

    Matrix3x3 transposed() const;

    double determinant() const;

    Matrix3x3 operator+(const Matrix3x3& other) const;
    Matrix3x3 operator-(const Matrix3x3& other) const;

    Matrix3x3 operator*(double scalar) const;
    Matrix3x3 operator/(double scalar) const;

    Matrix3x3 operator*(const Matrix3x3& other) const;

    Vector3D operator*(const Vector3D& vector) const;
};