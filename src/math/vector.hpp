#pragma once

struct Vector3D {
    double x;
    double y;
    double z;

    double magnitude() const;
    double magnitudeSquared() const;

    Vector3D normalized() const;

    double dot(const Vector3D& other) const;
    Vector3D cross(const Vector3D& other) const;

    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;

    Vector3D operator*(double scalar) const;
    Vector3D operator/(double scalar) const;
};

