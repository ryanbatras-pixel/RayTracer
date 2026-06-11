#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

#include <algorithm>
#include <atomic>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class camera {
public:
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 800;
    int samples_per_pixel = 100;
    int max_depth = 30;
    color background = color(0.02, 0.025, 0.04);

    double vfov = 40;
    point3 lookfrom = point3(0, 0, 0);
    point3 lookat = point3(0, 0, -1);
    vec3 vup = vec3(0, 1, 0);

    double defocus_angle = 0;
    double focus_dist = 10;

    void render(const hittable& world, const std::string& filename) {
        initialize();

        std::vector<color> pixels(static_cast<size_t>(image_width) * image_height);
        int thread_count = static_cast<int>(std::max(1u, std::thread::hardware_concurrency()));
        std::vector<std::thread> threads;
        std::atomic<int> next_row{0};

        auto worker = [&]() {
            while (true) {
                int j = next_row++;
                if (j >= image_height) break;

                for (int i = 0; i < image_width; i++) {
                    color pixel_color(0, 0, 0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    pixels[static_cast<size_t>(j) * image_width + i] = pixel_color;
                }

                if (j % 12 == 0) {
                    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                }
            }
        };

        for (int t = 0; t < thread_count; t++) threads.emplace_back(worker);
        for (auto& t : threads) t.join();

        std::ofstream out(filename);
        out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = 0; j < image_height; j++) {
            for (int i = 0; i < image_width; i++) {
                write_color(out, pixels[static_cast<size_t>(j) * image_width + i]);
            }
        }
        std::clog << "\rDone. Wrote " << filename << "                 \n";
    }

private:
    int image_height;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 u, v, w;
    vec3 defocus_disk_u;
    vec3 defocus_disk_v;
    double pixel_samples_scale;

    void initialize() {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = image_height < 1 ? 1 : image_height;
        pixel_samples_scale = 1.0 / samples_per_pixel;
        center = lookfrom;

        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        auto viewport_u = viewport_width * u;
        auto viewport_v = viewport_height * -v;

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        auto viewport_upper_left = center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
        auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    point3 defocus_disk_sample() const {
        auto p = random_in_unit_disk();
        return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        if (depth <= 0) return color(0, 0, 0);

        hit_record rec;
        if (!world.hit(r, 0.001, infinity, rec)) {
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5 * (unit_direction.y() + 1.0);
            return (1.0 - a) * background + a * color(0.25, 0.30, 0.42);
        }

        ray scattered;
        color attenuation;
        color emitted = rec.mat->emitted();

        if (!rec.mat->scatter(r, rec, attenuation, scattered)) return emitted;

        return emitted + attenuation * ray_color(scattered, depth - 1, world);
    }

    void write_color(std::ostream& out, color pixel_color) const {
        auto r = pixel_samples_scale * pixel_color.x();
        auto g = pixel_samples_scale * pixel_color.y();
        auto b = pixel_samples_scale * pixel_color.z();

        r = r > 0 ? std::sqrt(r) : 0;
        g = g > 0 ? std::sqrt(g) : 0;
        b = b > 0 ? std::sqrt(b) : 0;

        out << static_cast<int>(256 * clamp(r, 0.000, 0.999)) << ' '
            << static_cast<int>(256 * clamp(g, 0.000, 0.999)) << ' '
            << static_cast<int>(256 * clamp(b, 0.000, 0.999)) << '\n';
    }
};

#endif
