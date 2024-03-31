#ifndef RAY_TRACING_ALGEBRAUTILS_H
#define RAY_TRACING_ALGEBRAUTILS_H

#include <algorithm>

#include "vec3.hpp"

constexpr double EPS = 1e-6;

inline double max3(glm::dvec3 v) {
    return std::max(std::max(v.x, v.y), v.z);
}

inline double min3(glm::dvec3 v) {
    return std::min(std::min(v.x, v.y), v.z);
}

inline double sqr(double x) {
    return x * x;
}

inline double pow5(double x) {
    return x * sqr(sqr(x));
}

#endif //RAY_TRACING_ALGEBRAUTILS_H
