#include <algorithm>
#include <iostream>

#include "BVH.h"


void BVH::build(std::vector<std::shared_ptr<Object>> &&primitives) {
    primitives_ = std::move(primitives);
    root = build_node(0, primitives_.size());
    std::cout << "Build finished" << std::endl;
}

uint32_t BVH::build_node(uint32_t first, uint32_t count) {
    AABB aabb;
    for (auto i = first; i < first + count; i++) {
        aabb.extend(primitives_[i]->getAABB());
    }

    if (count <= kMaxNodeSize) {
        nodes.push_back(
                {.aabb = aabb, .left_child = kNoChild, .right_child = kNoChild, .first_primitive_id = first, .primitive_count = count,});
    } else {
        const auto diff = aabb.max_ - aabb.min_;

        int index = 0;
        for (int i = 1; i < 3; i++) {
            if (diff[i] > diff[index]) {
                index = i;
            }
        }

        auto mid = diff[index] / 2 + aabb.min_[index];

        const auto pred = [index, mid](const std::shared_ptr<Object> &primitive) {
            return primitive->position[index] < mid;
        };

        const auto it = std::partition(primitives_.begin() + first, primitives_.begin() + first + count, pred);
        const auto first_group_count = it - first - primitives_.begin();

        if (first_group_count == 0 || first_group_count == count) {
            nodes.push_back(
                    {.aabb = aabb, .left_child = kNoChild, .right_child = kNoChild, .first_primitive_id = first, .primitive_count = count,});
        } else {
            const auto left_child = build_node(first, first_group_count);
            const auto right_child = build_node(first + first_group_count, count - first_group_count);

            nodes.push_back(
                    {.aabb = aabb, .left_child = left_child, .right_child = right_child, .first_primitive_id = first, .primitive_count = 0,});
        }
    }
    return nodes.size() - 1;
}

void BVH::intersect(const Ray &ray, uint32_t vertex, SceneIntersection &scene_intersection) const {
    if (vertex == kNoChild) {
        return;
    }
    const auto &node = nodes[vertex];
    if (node.aabb.intersect(ray)) {
        for (std::size_t i = 0; i < node.primitive_count; i++) {
            const auto &object = primitives_[i + node.first_primitive_id];
            auto result = object->intersect(ray);
            if (result.t < scene_intersection.object_intersection.t) {
                scene_intersection.object_intersection = result;
                scene_intersection.object_id = i + node.first_primitive_id;
            }
        }

        intersect(ray, node.left_child, scene_intersection);
        intersect(ray, node.right_child, scene_intersection);
    }
}
