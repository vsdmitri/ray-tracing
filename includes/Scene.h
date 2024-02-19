#ifndef HW1_SCENE_H
#define HW1_SCENE_H

#include <vector>
#include <memory>

#include "simpleStructs.h"
#include "Object.h"

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

    Color intersect_ray(float pixel_x, float pixel_y);

    Color bg_color;
    Camera camera;
    std::vector<std::unique_ptr<Object>> objects;
};


#endif //HW1_SCENE_H
