#include "Box.h"

std::optional<float> Box::intersect(const Ray &ray) {
    float tx1 = (-s.x - ray.o.x) / ray.dir.x;
    float tx2 = (s.x - ray.o.x) / ray.dir.x;
    if (tx2 < tx1) std::swap(tx1, tx2);
    float ty1 = (-s.y - ray.o.y) / ray.dir.y;
    float ty2 = (s.y - ray.o.y) / ray.dir.y;
    if (ty2 < ty1) std::swap(ty1, ty2);
    float tz1 = (-s.z - ray.o.z) / ray.dir.z;
    float tz2 = (s.z - ray.o.z) / ray.dir.z;
    if (tz2 < tz1) std::swap(tz1, tz2);
    float t1 = std::max(tx1, std::max(ty1, tz1));
    float t2 = std::min(tx2, std::min(ty2, tz2));

    if (t2 < t1) return std::nullopt;

    if (t1 >= 0) return t1;
    if (t2 >= 0) return t2;

    return std::nullopt;
}

