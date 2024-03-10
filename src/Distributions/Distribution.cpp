#include "Distribution.h"

double Distribution::get_p_factor(const glm::dvec3 &d, const ObjectIntersection &intersection) const {
    return intersection.t * intersection.t / std::abs(glm::dot(intersection.normal, d));
}
