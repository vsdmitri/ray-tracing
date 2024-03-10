#include "Distribution.h"

double Distribution::get_p_factor(const glm::dvec3 &d, const ObjectIntersection &intersection) const {
    auto t2 = intersection.t * intersection.t;
    auto cos = std::abs(glm::dot(intersection.normal, d));
    return t2 / cos;
}
