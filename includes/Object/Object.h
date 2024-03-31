#ifndef HW1_OBJECT_H
#define HW1_OBJECT_H

#include <optional>

#include "gtc/quaternion.hpp"

#include "simpleStructs.h"
#include "geometryUtils.hpp"

enum class ObjectTag {
    Box,
    Ellipsoid,
    Plane,
};

struct Object {
    glm::dvec3 position = {0, 0, 0}, emission = {0, 0, 0};
    glm::dquat rotation = {1, 0, 0, 0}, inverse_rotation = {1, 0, 0, 0};
    Color color;
    double index_of_refraction;
    Material material = Material::DIFFUSE;

    [[nodiscard]] virtual ObjectIntersection intersect(Ray) const = 0;

   virtual ObjectTag getTag() const = 0;

    void prepare_ray(Ray &ray) const;

    void prepare_intersection_info(ObjectIntersection &intersection, const Ray &ray) const;

    virtual ~Object() = default;
};


#endif //HW1_OBJECT_H
