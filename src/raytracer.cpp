#include "ray.h"
#include "vector.h"

#include <algorithm>
#include <iostream>

using Color = Vector;

double hit_sphere(const Vector& center, double radius, const Ray& ray) {
    Vector oc = ray.origin - center;
    double a = ray.direction.length_squared();
    double half_b = oc.dot(ray.direction);
    double c = oc.length_squared() - radius * radius;
    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0) {
        return -1.0;
    }

    return (-half_b - std::sqrt(discriminant)) / a;
}

Color ray_color(const Ray& ray) {
    double t = hit_sphere(Vector(0, 0, -1), 0.5, ray);

    if (t > 0.0) {
        Vector normal = (ray.point_at(t) - Vector(0, 0, -1)).normalize();
        return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }

    Vector unit_direction = ray.direction.normalize();
    double blend = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - blend) * Color(1.0, 1.0, 1.0) + blend * Color(0.5, 0.7, 1.0);
}

void write_color(const Color& color) {
    int red = static_cast<int>(255.999 * std::clamp(color.x(), 0.0, 1.0));
    int green = static_cast<int>(255.999 * std::clamp(color.y(), 0.0, 1.0));
    int blue = static_cast<int>(255.999 * std::clamp(color.z(), 0.0, 1.0));

    std::cout << red << ' ' << green << ' ' << blue << '\n';
}

int main() {
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    const double viewport_height = 2.0;
    const double viewport_width = aspect_ratio * viewport_height;
    const double focal_length = 1.0;

    Vector camera_origin(0, 0, 0);
    Vector horizontal(viewport_width, 0, 0);
    Vector vertical(0, viewport_height, 0);
    Vector lower_left_corner =
        camera_origin - horizontal / 2 - vertical / 2 - Vector(0, 0, focal_length);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int y = image_height - 1; y >= 0; --y) {
        std::clog << "\rScanlines remaining: " << y << ' ';

        for (int x = 0; x < image_width; ++x) {
            double u = static_cast<double>(x) / (image_width - 1);
            double v = static_cast<double>(y) / (image_height - 1);
            Ray ray(camera_origin, lower_left_corner + u * horizontal + v * vertical - camera_origin);
            write_color(ray_color(ray));
        }
    }

    std::clog << "\nDone.\n";
    return 0;
}

