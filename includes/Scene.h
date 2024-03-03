#ifndef HW1_SCENE_H
#define HW1_SCENE_H

#include <vector>
#include <memory>

#include "simpleStructs.h"
#include "Object.h"
#include "RandomGenerator.h"

struct Scene {
    struct Camera {
        uint32_t width, height;
        glm::vec3 position, right, up, forward;
        float fov_tg2_x;
        float fov_tg2_y;

        void init();

        [[nodiscard]] Ray get_ray(float pixel_x, float pixel_y) const;
    };

    void init();

    Color get_color(const Ray &, RandomGenerator &r, uint8_t depth = 0) const;

    Color get_pixel_color(uint32_t pixel_x, uint32_t pixel_y, RandomGenerator &r) const;

    [[nodiscard]] SceneIntersection
    intersect_ray(const Ray &ray, float max_dist = std::numeric_limits<float>::max()) const;

    Color bg_color;
    Camera camera;

    uint8_t ray_depth = 8;
    uint16_t samples = 1;

    std::vector<std::unique_ptr<Object>> objects;

    [[nodiscard]] Color
    process_diffuse(const SceneIntersection &, const Ray &ray, uint8_t depth, RandomGenerator &r) const;

    [[nodiscard]] Color
    process_metalic(const SceneIntersection &, const Ray &ray, uint8_t depth, RandomGenerator &r) const;

    Color process_dielectric(const SceneIntersection &, const Ray &ray, uint8_t depth, RandomGenerator &r) const;

    Color get_reflected_color(const glm::vec3 &point, const glm::vec3 &normal, const Ray &ray,
                              uint8_t depth, RandomGenerator &rnd) const;

    static constexpr const float SHIFT = 1e-4;
};


#endif //HW1_SCENE_H
