#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <vector>

constexpr double kInfinity = std::numeric_limits<double>::infinity();
constexpr double kPi = 3.1415926535897932385;

double degrees_to_radians(double degrees) {
    return degrees * kPi / 180.0;
}

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

double random_double() {
    static std::mt19937 generator(42);
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

struct Vec3 {
    double x;
    double y;
    double z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    Vec3 operator-() const { return Vec3(-x, -y, -z); }
    Vec3 operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); }
    Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }
    Vec3 operator*(const Vec3& other) const { return Vec3(x * other.x, y * other.y, z * other.z); }
    Vec3 operator*(double t) const { return Vec3(x * t, y * t, z * t); }
    Vec3 operator/(double t) const { return *this * (1.0 / t); }

    Vec3& operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    double length_squared() const { return x * x + y * y + z * z; }
    double length() const { return std::sqrt(length_squared()); }

    bool near_zero() const {
        const auto s = 1e-8;
        return std::fabs(x) < s && std::fabs(y) < s && std::fabs(z) < s;
    }
};

using Point3 = Vec3;
using Color = Vec3;

Vec3 operator*(double t, const Vec3& v) {
    return v * t;
}

double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

Vec3 unit_vector(const Vec3& v) {
    return v / v.length();
}

Vec3 random_in_unit_sphere() {
    while (true) {
        auto p = Vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
        if (p.length_squared() < 1) return p;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dot(v, n) * n;
}

Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = std::min(dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

struct Ray {
    Point3 origin;
    Vec3 direction;

    Ray() = default;
    Ray(const Point3& origin_, const Vec3& direction_) : origin(origin_), direction(direction_) {}

    Point3 at(double t) const {
        return origin + t * direction;
    }
};

struct Material;

struct HitRecord {
    Point3 point;
    Vec3 normal;
    std::shared_ptr<Material> material;
    double t = 0;
    bool front_face = false;

    void set_face_normal(const Ray& ray, const Vec3& outward_normal) {
        front_face = dot(ray.direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

struct Hittable {
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const = 0;
};

struct Material {
    virtual ~Material() = default;
    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;
};

struct Lambertian : public Material {
    Color albedo;

    explicit Lambertian(const Color& albedo_) : albedo(albedo_) {}

    bool scatter(const Ray&, const HitRecord& record, Color& attenuation, Ray& scattered) const override {
        auto scatter_direction = record.normal + random_unit_vector();
        if (scatter_direction.near_zero()) scatter_direction = record.normal;
        scattered = Ray(record.point, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

struct Metal : public Material {
    Color albedo;
    double fuzz;

    Metal(const Color& albedo_, double fuzz_) : albedo(albedo_), fuzz(fuzz_ < 1 ? fuzz_ : 1) {}

    bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override {
        Vec3 reflected = reflect(unit_vector(ray.direction), record.normal);
        scattered = Ray(record.point, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return dot(scattered.direction, record.normal) > 0;
    }
};

struct Dielectric : public Material {
    double index_of_refraction;

    explicit Dielectric(double index_of_refraction_) : index_of_refraction(index_of_refraction_) {}

    static double reflectance(double cosine, double ref_idx) {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }

    bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double refraction_ratio = record.front_face ? (1.0 / index_of_refraction) : index_of_refraction;

        Vec3 unit_direction = unit_vector(ray.direction);
        double cos_theta = std::min(dot(-unit_direction, record.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        Vec3 direction;
        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
            direction = reflect(unit_direction, record.normal);
        } else {
            direction = refract(unit_direction, record.normal, refraction_ratio);
        }

        scattered = Ray(record.point, direction);
        return true;
    }
};
