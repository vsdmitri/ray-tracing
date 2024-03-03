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

Color Scene::get_pixel_color(uint32_t pixel_x, uint32_t pixel_y, RandomGenerator &rnd) const {
    Color color = {0, 0, 0};
    for (std::size_t i = 0; i < samples; i++) {
        Ray ray = camera.get_ray(pixel_x + rnd.get_random_float(), pixel_y + rnd.get_random_float());
        color += get_color(ray, rnd);
    }
    return color / static_cast<float>(samples);
}

Color Scene::get_color(const Ray &ray, RandomGenerator &rnd, uint8_t depth) const {
    if (depth == ray_depth) return {0, 0, 0};
    auto intersection_result = intersect_ray(ray);
    if (intersection_result.object_id == SceneIntersection::NO_OBJECT_ID) return bg_color;

    const auto &object = objects[intersection_result.object_id];
    static const float SHIFT = 1e-4;
    glm::vec3 point = ray.o + ray.dir * intersection_result.object_intersection.t +
                      SHIFT * intersection_result.object_intersection.normal;

    Color color = object->color;

    switch (object->material) {
        case Material::DIFFUSE:
            return process_diffuse(intersection_result, color, point, depth, rnd);
        case Material::METALLIC:
            return process_metalic(color, point, intersection_result.object_intersection.normal, ray, depth, rnd);
        case Material::DIELECTRIC:
            return process_dielectric(intersection_result, ray, depth, rnd);
    }
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

Color Scene::get_reflected_color(const glm::vec3 &point, const glm::vec3 &normal, const Ray &ray,
                                 uint8_t depth, RandomGenerator &rnd) const {
    glm::vec3 new_direction = ray.dir - 2.f * normal * glm::dot(normal, ray.dir);
    Ray new_ray = {point, new_direction};
    return get_color(new_ray, rnd, depth + 1);
}

Color Scene::process_diffuse(const SceneIntersection &scene_intersection, const Color &color, const glm::vec3 &point,
                             uint8_t depth, RandomGenerator &rnd) const {
    auto &object = objects[scene_intersection.object_id];
    auto w = rnd.get_random_semi_sphere_vec(scene_intersection.object_intersection.normal);
    Ray new_ray = {point, w};
//    E+2C·Lin(ω)·(ω·n)
    return object->emission + 2.f * object->color * get_color(new_ray, rnd, depth + 1) *
                              glm::dot(w, scene_intersection.object_intersection.normal);
}

Color Scene::process_metalic(const Color &color, const glm::vec3 &point, const glm::vec3 &normal, const Ray &ray,
                             uint8_t depth, RandomGenerator &rnd) const {

    return color * get_reflected_color(point, normal, ray, depth, rnd);
}

Color Scene::process_dielectric(const SceneIntersection &scene_intersection, const Ray &ray, uint8_t depth,
                                RandomGenerator &rnd) const {
    auto &object = objects[scene_intersection.object_id];
    float n1 = 1;
    float n2 = object->index_of_reflection;
    if (scene_intersection.object_intersection.is_inside) std::swap(n1, n2);
    auto &normal = scene_intersection.object_intersection.normal;

    static const float SHIFT = 1e-4;
    glm::vec3 shifted_forward_point = ray.o + ray.dir * scene_intersection.object_intersection.t -
                                      SHIFT * normal;
    glm::vec3 shifted_back_point = ray.o + ray.dir * scene_intersection.object_intersection.t +
                                   SHIFT * normal;

    float cos_theta1 = glm::dot(-ray.dir, normal);
    float sin_theta2 = n1 / n2 * sqrt(1 - cos_theta1 * cos_theta1);

    if (sin_theta2 > 1) return get_reflected_color(shifted_back_point, normal, ray, depth, rnd);

    float cos_theta2 = sqrt(1 - sin_theta2 * sin_theta2);
    glm::vec3 refracted_direction = n1 / n2 * ray.dir + (n1 / n2 * cos_theta1 - cos_theta2) * normal;

    float R0 = (n1 - n2) * (n1 - n2) / (n1 + n2) / (n1 + n2);
    float reflection_factor = R0 + (1 - R0) * std::pow((1 - cos_theta1), 5);
    if (rnd.get_random_float() <= reflection_factor) {
        return get_reflected_color(shifted_back_point, normal, ray, depth, rnd);
    } else {
        Ray refracted_ray = {shifted_forward_point, refracted_direction};
        Color refracted_color = get_color(refracted_ray, rnd, depth + 1);

        if (!scene_intersection.object_intersection.is_inside) refracted_color *= object->color;
        return refracted_color;
    }
}
