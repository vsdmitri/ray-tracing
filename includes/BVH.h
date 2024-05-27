#ifndef RAY_TRACING_BVH_H
#define RAY_TRACING_BVH_H

#include <vector>
#include <memory>

#include "Object.h"
#include "AABB.h"

struct Node {
    AABB aabb;
    uint32_t left_child;
    uint32_t right_child;
    uint32_t first_primitive_id;
    uint32_t primitive_count;
};

struct BVH {
    std::vector<Node> nodes;
    uint32_t root{0};

    void build(std::vector<std::shared_ptr<Object>> &&primitives);

    uint32_t build_node(uint32_t first, uint32_t count);

    void intersect(const Ray &ray, uint32_t vertex, SceneIntersection &scene_intersection) const;

    constexpr static uint32_t kMaxNodeSize = 4;
    constexpr static uint32_t kNoChild = -1;

    std::vector<std::shared_ptr<Object>> primitives_;
};


#endif //RAY_TRACING_BVH_H
