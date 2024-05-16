#include "TriangleDistribution.h"

glm::dvec3
TriangleDistribution::sample(const glm::dvec3 &x, const glm::dvec3 &, RandomGenerator &r, bool) const {
    double u = r.get_random_float(), v = r.get_random_float();
    if (u + v >= 1) {
        u = 1 - u;
        v = 1 - v;
    }

    glm::dvec3 result = triangle_->a_ + (triangle_->b_ - triangle_->a_) * u + (triangle_->c_ - triangle_->a_) * v;
    fast_rotate(triangle_->rotation, result);
    return glm::normalize(result + triangle_->position - x);
}

double TriangleDistribution::pdf(const glm::dvec3 &x, const glm::dvec3 &, const glm::dvec3 &d) const {
    auto ray = Ray{x, d};

    auto intersection = triangle_->intersect(ray);
    double result = 0;
    if (intersection.t < std::numeric_limits<double>::max()) {
        auto y = x + d * intersection.t;
        result += 1 / area_ * get_p_factor(x, y, intersection.normal);
    }

    return result;
}
