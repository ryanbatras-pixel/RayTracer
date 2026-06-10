#include <fstream>
#include <cmath>

struct Vec3 {
    double x, y, z;

    Vec3(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_) {}

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    double dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
};

bool hitSphere(Vec3 center, double radius, Vec3 rayOrigin, Vec3 rayDir) {

    Vec3 oc = rayOrigin - center;

    double a = rayDir.dot(rayDir);
    double b = 2.0 * oc.dot(rayDir);
    double c = oc.dot(oc) - radius * radius;

    double discriminant = b * b - 4 * a * c;

    return discriminant >= 0;
}

int main() {

    const int width = 256;
    const int height = 256;

    std::ofstream image("output.ppm");

    image << "P3\n";
    image << width << " " << height << "\n255\n";

    Vec3 sphereCenter(0, 0, -1);
    Vec3 rayOrigin(0, 0, 0);

    for (int y = 0; y < height; y++) {

        for (int x = 0; x < width; x++) {

            double u = (x - width / 2.0) / (width / 2.0);
            double v = (height / 2.0 - y) / (height / 2.0);

            Vec3 rayDir(u, v, -1);

            if (hitSphere(sphereCenter, 0.5, rayOrigin, rayDir)) {
                image << "255 0 0\n";
            }
            else {
                image << "100 150 255\n";
            }
        }
    }

    image.close();

    return 0;
}
