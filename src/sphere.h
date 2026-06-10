#pragma once

#include "ray.h"

struct Sphere {
    Vec3 center;
    double radius;

    Sphere(const Vec3& c, double r)
        : center(c), radius(r) {}

    bool hit(const Ray& ray) const {
        Vec3 oc = ray.origin - center;

        double a = ray.direction.dot(ray.direction);
        double b = 2.0 * oc.dot(ray.direction);
        double c = oc.dot(oc) - radius * radius;

        double discriminant = b * b - 4 * a * c;

        return discriminant >= 0;
    }
};
