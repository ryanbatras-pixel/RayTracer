#pragma once

#include "ray.h"

class Sphere {
public:
    Vec3 center;
    double radius;
    Vec3 color;

    Sphere(Vec3 c,double r,Vec3 col)
        : center(c), radius(r), color(col) {}

    bool intersect(const Ray& ray,double& t) {

        Vec3 oc=ray.origin-center;

        double a=ray.direction.dot(ray.direction);
        double b=2.0*oc.dot(ray.direction);
        double c=oc.dot(oc)-radius*radius;

        double discriminant=b*b-4*a*c;

        if(discriminant<0)
            return false;

        t=(-b-sqrt(discriminant))/(2*a);

        return t>0;
    }
};
