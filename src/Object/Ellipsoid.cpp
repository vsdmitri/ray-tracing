#include "Ellipsoid.h"

std::optional<float> Ellipsoid::intersect(const Ray &ray) {
        float c = glm::dot(ray.o / rs, ray.o / rs) - 1;
        float b = 2 * glm::dot(ray.o / rs, ray.dir / rs);
        float a = glm::dot(ray.dir / rs, ray.dir / rs);
        float D = b * b - 4 * a * c;
        if (D < 0) return std::nullopt;
        D = sqrt(D);

        float t1 = (-b - D) / (2 * a);
        float t2 = (-b + D) / (2 * a);

        if (t2 < t1) std::swap(t1, t2);
        if (t1 >= 0) return t1;
        if (t2 >= 0) return t2;
        return std::nullopt;
}
