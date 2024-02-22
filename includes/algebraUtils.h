#ifndef RAY_TRACING_ALGEBRAUTILS_H
#define RAY_TRACING_ALGEBRAUTILS_H

#include <algorithm>

#include "vec3.hpp"

constexpr double EPS = 1e-5;

double max3(glm::dvec3 v);
double min3(glm::dvec3 v);

#endif //RAY_TRACING_ALGEBRAUTILS_H
