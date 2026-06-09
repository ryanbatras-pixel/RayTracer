#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray {
public:
    Vector origin;
    Vector direction;

    Ray(const Vector& origin_, const Vector& direction_)
        : origin(origin_), direction(direction_) {}

    Vector point_at(double distance) const {
        return origin + direction * distance;
    }
};

#endif

