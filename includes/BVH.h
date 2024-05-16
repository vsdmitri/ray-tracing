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
    uint32_t root;

    void build_node(std::vector<std::shared_ptr<Object>> &primitives, uint32_t first, uint32_t count);

    constexpr static uint32_t kMinSize = 2;
};


#endif //RAY_TRACING_BVH_H
