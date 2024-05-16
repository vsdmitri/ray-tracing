#include "BVH.h"

void BVH::build_node(std::vector<std::shared_ptr<Object>> &/*primitives*/, uint32_t /*first*/, uint32_t count) {
    if (count < kMinSize) {
//        AABB aabb;
//        uint32_t left_child;
//        uint32_t right_child;
//        uint32_t first_primitive_id;
//        uint32_t primitive_count;
        nodes.emplace_back();
    }
}
