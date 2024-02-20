#ifndef HW1_SIMPLESTRUCTS_H
#define HW1_SIMPLESTRUCTS_H

#include "vec3.hpp"

typedef glm::vec3 Color;

struct Ray {
    glm::vec3 o, dir;
};

// TODO: check normals
struct ObjectIntersection {
    float t = std::numeric_limits<float>::max();
    glm::vec3 normal;
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
