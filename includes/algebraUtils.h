#ifndef RAY_TRACING_ALGEBRAUTILS_H
#define RAY_TRACING_ALGEBRAUTILS_H

#include <algorithm>

#include "vec3.hpp"

constexpr float EPS = 1e-6;

float max3(glm::vec3 v);
float min3(glm::vec3 v);

#endif //RAY_TRACING_ALGEBRAUTILS_H
