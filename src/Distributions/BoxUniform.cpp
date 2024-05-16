#include "BoxUniform.h"

glm::dvec3 BoxUniform::sample(const glm::dvec3 &x, const glm::dvec3 &, RandomGenerator &r, bool) const {
    double u = r.get_random_float(0., area_);
    double a = r.get_random_float(-1., 1.), b = r.get_random_float(-1., 1.);
    const auto &s = box_->s_;

    glm::dvec3 result;
    if (u < w_.x) result = {s.x, s.y * a, s.z * b};
    else if (u < 2 * w_.x) result = {-s.x, s.y * a, s.z * b};
    else if (u < 2 * w_.x + w_.y) result = {s.x * a, s.y, s.z * b};
    else if (u < 2 * (w_.x + w_.y)) result = {s.x * a, -s.y, s.z * b};
    else if (u < 2 * (w_.x + w_.y) + w_.z) result = {s.x * a, s.y * b, s.z};
    else result = {s.x * a, s.y * b, -s.z};

    fast_rotate(box_->rotation, result);
    return glm::normalize(result + box_->position - x);
}

double BoxUniform::pdf(const glm::dvec3 &x, const glm::dvec3 &, const glm::dvec3 &d) const {
    static const double SHIFT = 1e-4;
    auto ray = Ray{x, d};
    double result = 0.;

    auto intersection = box_->intersect(ray);
    if (intersection.t < std::numeric_limits<double>::max()) {
        auto y = x + d * (intersection.t + SHIFT);
        result += area_inverse_ * get_p_factor(x, y, intersection.normal);
        ray.o = y;
        intersection = box_->intersect(ray);
        if (intersection.t < std::numeric_limits<double>::max()) {
            y = ray.o + d * intersection.t;
            result += area_inverse_ * get_p_factor(x, y, intersection.normal);
        }
    }

    return result;
}


