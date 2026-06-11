#ifndef SCENE_H
#define SCENE_H

#include "material.h"
#include "sphere.h"

inline hittable_list solar_system_scene() {
    hittable_list world;

    auto space_floor = make_shared<lambertian>(
        color(0.12, 0.12, 0.12));

    world.add(make_shared<sphere>(
        point3(0, -1000, 0),
        1000,
        space_floor));

    auto sun = make_shared<diffuse_light>(
        color(7.0, 6.5, 4.5));

    auto mercury = make_shared<lambertian>(
        color(0.55, 0.55, 0.55));

    auto venus = make_shared<lambertian>(
        color(0.90, 0.75, 0.35));

    auto earth = make_shared<lambertian>(
        color(0.20, 0.45, 1.00));

    auto moon = make_shared<lambertian>(
        color(0.80, 0.80, 0.80));

    auto mars = make_shared<lambertian>(
        color(0.80, 0.30, 0.20));

    auto jupiter = make_shared<lambertian>(
        color(0.90, 0.70, 0.45));

    auto saturn = make_shared<lambertian>(
        color(0.95, 0.85, 0.55));

    auto ring = make_shared<metal>(
        color(0.85, 0.85, 0.85),
        0.05);

    world.add(make_shared<sphere>(
        point3(0, 2.5, 0),
        2.0,
        sun));

    world.add(make_shared<sphere>(
        point3(4, 0.2, 0),
        0.15,
        mercury));

    world.add(make_shared<sphere>(
        point3(6, 0.3, 0),
        0.30,
        venus));

    world.add(make_shared<sphere>(
        point3(8, 0.35, 0),
        0.35,
        earth));

    world.add(make_shared<sphere>(
        point3(8.7, 0.35, 0),
        0.08,
        moon));

    world.add(make_shared<sphere>(
        point3(10, 0.25, 0),
        0.25,
        mars));

    world.add(make_shared<sphere>(
        point3(14, 1.0, 0),
        1.0,
        jupiter));

    world.add(make_shared<sphere>(
        point3(19, 0.9, 0),
        0.9,
        saturn));

    for (int i = 0; i < 60; i++) {
        double angle = 2 * pi * i / 60.0;
        double radius = 1.6;

        world.add(make_shared<sphere>(
            point3(
                19 + radius * std::cos(angle),
                0.9,
                radius * std::sin(angle)
            ),
            0.05,
            ring));
    }

    return world;
}

#endif
