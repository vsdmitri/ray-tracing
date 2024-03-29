#include "Distribution.h"

double Distribution::get_p_factor(const glm::dvec3& x, const glm::dvec3& y, const glm::dvec3& n) const {
    auto w = glm::normalize(x - y);
    auto dist = glm::length(x - y);
    auto cos = std::abs(glm::dot(n, w));
    return dist * dist / cos;
}
