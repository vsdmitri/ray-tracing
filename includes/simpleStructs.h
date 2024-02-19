#ifndef HW1_SIMPLESTRUCTS_H
#define HW1_SIMPLESTRUCTS_H

#include "vec3.hpp"

struct Color {
    uint8_t r = 0, g = 0, b = 0;
};

struct Ray {
    glm::vec3 o, dir;
};

#endif //HW1_SIMPLESTRUCTS_H
