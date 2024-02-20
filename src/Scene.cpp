#include "Scene.h"

void Scene::Camera::init() {
    fov_tg2_y = fov_tg2_x * height / width;
}

Ray Scene::Camera::get_ray(float pixel_x, float pixel_y) const {
    float X = (2 * pixel_x / width - 1) * fov_tg2_x;
    float Y = -(2 * pixel_y / height - 1) * fov_tg2_y;
    return {position, glm::normalize(X * right + Y * up + forward)};

}

void Scene::init() {
    camera.init();
}

Color Scene::get_color(float pixel_x, float pixel_y) const {
    Ray ray = camera.get_ray(pixel_x, pixel_y);
    auto intersection_result = intersect_ray(ray);
    if (intersection_result.object_id == SceneIntersection::NO_OBJECT_ID) return bg_color;

    static const float SHIFT = 1e-4;
    glm::vec3 point = ray.o + ray.dir * intersection_result.object_intersection.t + SHIFT * intersection_result.object_intersection.normal;

    // diffuse
    Color color = objects[intersection_result.object_id]->color;
    glm::vec3 additional_color = ambient_light;
    for (const auto &light: lights) {
        float dist = light->get_distance(point);
        Ray to_light = {point, light->get_on_light_direction(point)};
        auto intersection = intersect_ray(to_light, dist);
        if (intersection.object_id == SceneIntersection::NO_OBJECT_ID) {
            additional_color += light->get_intensity(point) *
                                std::max(0.f, glm::dot(to_light.dir, intersection_result.object_intersection.normal));
        }
    }

    return color * additional_color;
}

SceneIntersection Scene::intersect_ray(const Ray &ray, float max_dist) const {
    SceneIntersection scene_intersection;
    scene_intersection.object_id = SceneIntersection::NO_OBJECT_ID;
    scene_intersection.object_intersection.t = max_dist;

    for (std::size_t i = 0; i < objects.size(); i++) {
        const auto &object = objects[i];
        auto result = object->intersect(ray);
        if (result.has_value() && result.value().t < scene_intersection.object_intersection.t) {
            scene_intersection.object_intersection = result.value();
            scene_intersection.object_id = i;
        }
    }

    return scene_intersection;
}
