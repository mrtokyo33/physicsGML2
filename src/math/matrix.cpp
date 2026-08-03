#include "matrix3x3.hpp"

Matrix3x3::Matrix3x3()
    : m{
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}
    }
{
}

Matrix3x3::Matrix3x3(
    double m00, double m01, double m02,
    double m10, double m11, double m12,
    double m20, double m21, double m22
)
    : m{
        {m00, m01, m02},
        {m10, m11, m12},
        {m20, m21, m22}
    }
{
}

Matrix3x3 Matrix3x3::identity() {
    return Matrix3x3{
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    };
}

Matrix3x3 Matrix3x3::transposed() const {
    return Matrix3x3{
        m[0][0], m[1][0], m[2][0],
        m[0][1], m[1][1], m[2][1],
        m[0][2], m[1][2], m[2][2]
    };
}

double Matrix3x3::determinant() const {
    return
        m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
        m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
        m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
    Matrix3x3 result;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.m[i][j] = m[i][j] + other.m[i][j];

    return result;
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const {
    Matrix3x3 result;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.m[i][j] = m[i][j] - other.m[i][j];

    return result;
}

Matrix3x3 Matrix3x3::operator*(double scalar) const {
    Matrix3x3 result;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.m[i][j] = m[i][j] * scalar;

    return result;
}

Matrix3x3 Matrix3x3::operator/(double scalar) const {
    Matrix3x3 result;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.m[i][j] = m[i][j] / scalar;

    return result;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const {
    Matrix3x3 result;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {

            result.m[row][col] =
                m[row][0] * other.m[0][col] +
                m[row][1] * other.m[1][col] +
                m[row][2] * other.m[2][col];
        }
    }

    return result;
}

Vector3D Matrix3x3::operator*(const Vector3D& vector) const {
    return Vector3D{
        m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z,
        m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z,
        m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z
    };
}