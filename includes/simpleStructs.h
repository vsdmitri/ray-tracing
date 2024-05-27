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
    static const int NO_OBJECT_ID = std::numeric_limits<int>::max();
    int object_id = NO_OBJECT_ID;
    ObjectIntersection object_intersection;
};

enum struct Material {
    DIFFUSE,
    METALLIC,
    DIELECTRIC,
};

#endif //HW1_SIMPLESTRUCTS_H
