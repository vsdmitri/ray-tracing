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
        glm::vec3 position, right, up, forward;
        float fov_tg2_x;
        float fov_tg2_y;

        void init();

        [[nodiscard]] Ray get_ray(float pixel_x, float pixel_y) const;
    };

    void init();

    Color get_color(float pixel_x, float pixel_y) const;

    [[nodiscard]] SceneIntersection
    intersect_ray(const Ray &ray, float max_dist = std::numeric_limits<float>::max()) const;

    Color bg_color;
    Camera camera;

    glm::vec3 ambient_light;
    uint8_t ray_depth;

    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Light>> lights;
};


#endif //HW1_SCENE_H
