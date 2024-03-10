#include "EllipsoidDistribution.h"

glm::dvec3 EllipsoidDistribution::sample(const glm::dvec3 &x, const glm::dvec3 &, RandomGenerator &r) const {
    return glm::normalize(ellipsoid_->rs * r.get_random_sphere_vec() + ellipsoid_->position - x);
}

double EllipsoidDistribution::pdf(const glm::dvec3 &x, const glm::dvec3 &, const glm::dvec3 &d) const {
    auto ray = Ray{x, d};
    double result = 0.;

    auto intersection = ellipsoid_->intersect(ray);
    if (intersection.t != std::numeric_limits<double>::max()) {
        auto point_on_sphere = ray.o + d * intersection.t - ellipsoid_->position;
        glm::dvec3 nn2 = point_on_sphere / ellipsoid_->rs;
        nn2 *= nn2;
        result += get_p_factor(d, intersection) * 0.25 * M_1_PI / sqrt(glm::dot(nn2, rr2));
        intersection = ellipsoid_->intersect(ray);
        ray.o += d * (intersection.t + EPS);
        if (intersection.t != std::numeric_limits<double>::max()) {
            point_on_sphere = ray.o + d * intersection.t - ellipsoid_->position;
            nn2 = point_on_sphere / ellipsoid_->rs;
            nn2 *= nn2;
            result += get_p_factor(d, intersection) * 0.25 * M_1_PI / sqrt(glm::dot(nn2, rr2));
        }
    }

    return result;
}