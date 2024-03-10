#include "algebraUtils.h"

double max3(glm::dvec3 v) {
    return std::max(std::max(v.x, v.y), v.z);
}

double min3(glm::dvec3 v) {
    return std::min(std::min(v.x, v.y), v.z);
}