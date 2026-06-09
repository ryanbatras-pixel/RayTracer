#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

class Vector {
public:
    double v[3];

    Vector() : v{0, 0, 0} {}
    Vector(double x, double y, double z) : v{x, y, z} {}

    double x() const { return v[0]; }
    double y() const { return v[1]; }
    double z() const { return v[2]; }

    Vector operator-() const {
        return Vector(-v[0], -v[1], -v[2]);
    }

    Vector operator+(const Vector& other) const {
        return Vector(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
    }

    Vector operator-(const Vector& other) const {
        return Vector(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
    }

    Vector operator*(double scalar) const {
        return Vector(v[0] * scalar, v[1] * scalar, v[2] * scalar);
    }

    Vector operator/(double scalar) const {
        return *this * (1.0 / scalar);
    }

    double length_squared() const {
        return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    Vector normalize() const {
        return *this / length();
    }

    double dot(const Vector& other) const {
        return v[0] * other.v[0] + v[1] * other.v[1] + v[2] * other.v[2];
    }

    Vector cross(const Vector& other) const {
        return Vector(
            v[1] * other.v[2] - v[2] * other.v[1],
            v[2] * other.v[0] - v[0] * other.v[2],
            v[0] * other.v[1] - v[1] * other.v[0]
        );
    }
};

inline Vector operator*(double scalar, const Vector& vector) {
    return vector * scalar;
}

#endif

