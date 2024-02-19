#include "Scene.h"

void Scene::Camera::init() {
    fov_tg2_y = fov_tg2_x * height / width;
}

Ray Scene::Camera::get_ray(float pixel_x, float pixel_y) const {
    float X = (2 * pixel_x / width - 1) * fov_tg2_x;
    float Y = -(2 * pixel_y / height - 1) * fov_tg2_y;
    return {position, X * right + Y * up + forward};

}

void Scene::init() {
    camera.init();
}

Color Scene::intersect_ray(float pixel_x, float pixel_y) {
    Ray ray = camera.get_ray(pixel_x, pixel_y);
    float dist = std::numeric_limits<float>::max();
    Color color = bg_color;

    for (const auto &object: objects) {
        Ray target_ray = object->prepare_ray(ray);
        auto result = object->intersect(target_ray);
        if (result.has_value() && result.value() < dist) {
            dist = result.value();
            color = object->color;
        }
    }

    return color;
}
