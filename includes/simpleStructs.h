#ifndef HW1_SIMPLESTRUCTS_H
#define HW1_SIMPLESTRUCTS_H

#include "vec3.hpp"

typedef glm::dvec3 Color;

struct Ray {
    glm::dvec3 o, dir;
};

struct ObjectIntersection {
    double t = std::numeric_limits<double>::max();
    glm::dvec3 normal;
    bool is_inside;
};

struct SceneIntersection {
    static const std::size_t NO_OBJECT_ID = -1;
    std::size_t object_id = NO_OBJECT_ID;
    ObjectIntersection object_intersection;
};

enum struct Material {
    DIFFUSE,
    METALLIC,
    DIELECTRIC,
};

#endif //HW1_SIMPLESTRUCTS_H
