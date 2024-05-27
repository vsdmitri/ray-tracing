#ifndef HW1_SCENE_H
#define HW1_SCENE_H

#include <vector>
#include <memory>

#include "simpleStructs.h"
#include "Object.h"
#include "Distribution.h"
#include "MixDistribution.h"
#include "Cosine.h"
#include "BVH.h"
#include "Plane.h"

struct Scene {
    struct Camera {
        void init();

        [[nodiscard]] Ray get_ray(double pixel_x, double pixel_y) const;

        uint32_t width, height;
        glm::dvec3 position, right, up, forward;
        double fov_tg2_x;
        double fov_tg2_y;

    };

    void init(std::vector<std::unique_ptr<Distribution>> &&light_distributions,
              std::vector<std::shared_ptr<Object>>&& objects);

    Color get_color(const Ray &, RandomGenerator &r, uint8_t depth = 0) const;

    Color get_pixel_color(uint32_t pixel_x, uint32_t pixel_y, RandomGenerator &r) const;

    [[nodiscard]] SceneIntersection
    intersect_ray(const Ray &ray) const;

    [[nodiscard]] Color
    process_diffuse(const SceneIntersection &, const Ray &ray, uint8_t depth, RandomGenerator &r) const;

    [[nodiscard]] Color
    process_metalic(const SceneIntersection &, const Ray &ray, uint8_t depth, RandomGenerator &r) const;

    Color process_dielectric(const SceneIntersection &, const Ray &ray, uint8_t depth, RandomGenerator &r) const;

    Color get_reflected_color(const glm::dvec3 &point, const glm::dvec3 &normal, const Ray &ray,
                              uint8_t depth, RandomGenerator &rnd) const;

    static constexpr const double SHIFT = 1e-5;

    Color bg_color;
    Camera camera;

    uint8_t ray_depth = 8;
    uint16_t samples = 1;

    std::unique_ptr<Distribution> sampler;

    BVH objects_bvh_;
    std::vector<std::shared_ptr<Object>> planes_;
};


#endif //HW1_SCENE_H
