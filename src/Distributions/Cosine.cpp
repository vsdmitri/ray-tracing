#include "Cosine.h"

glm::dvec3 Cosine::sample(const glm::dvec3 &, const glm::dvec3 &n, RandomGenerator &r, bool) const {
    auto v = r.get_random_sphere_vec();
    auto v_new = glm::normalize(v + n);
    return v_new;
}

double Cosine::pdf(const glm::dvec3 &, const glm::dvec3 &n, const glm::dvec3 &d) const {
    double dot = glm::dot(d, n);
    if (dot < 0) return 0;
    else return dot * static_cast<double> (M_1_PI);
}
