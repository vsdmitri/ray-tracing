#ifndef HW1_SCENE_H
#define HW1_SCENE_H

#include <vector>
#include <memory>

#include "simpleStructs.h"
#include "Object.h"
#include "Light.h"

struct Scene {
    struct Camera {
        uint32_t width, height;
        glm::dvec3 position, right, up, forward;
        double fov_tg2_x;
        double fov_tg2_y;

        void init();

        [[nodiscard]] Ray get_ray(double pixel_x, double pixel_y) const;
    };

    void init();

    Color get_color(const Ray &, uint8_t depth = 0) const;

    Color get_pixel_color(double pixel_x, double pixel_y) const;

    [[nodiscard]] SceneIntersection
    intersect_ray(const Ray &ray, double max_dist = std::numeric_limits<double>::max()) const;

    Color bg_color;
    Camera camera;

    glm::dvec3 ambient_light = glm::dvec3(0);
    uint8_t ray_depth;

    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Light>> lights;

    [[nodiscard]] Color process_diffuse(const Color &color, const glm::dvec3 &point, const glm::dvec3 &normal) const;

    [[nodiscard]] Color
    process_metalic(const Color &color, const glm::dvec3 &point, const glm::dvec3 &normal, const Ray &ray,
                    uint8_t depth) const;

    Color process_dielectric(const SceneIntersection &, const Ray &ray, uint8_t depth) const;
};


#endif //HW1_SCENE_H
