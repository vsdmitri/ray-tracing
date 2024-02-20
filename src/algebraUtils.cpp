#include "algebraUtils.h"

float max3(glm::vec3 v) {
    return std::max(std::max(v.x, v.y), v.z);
}

float min3(glm::vec3 v) {
    return std::min(std::min(v.x, v.y), v.z);
}