#include "Scene.h"

void Scene::Camera::init() {
    fov_tg2_y = fov_tg2_x * height / width;
}

Ray Scene::Camera::get_ray(double pixel_x, double pixel_y) const {
    double X = (2 * pixel_x / width - 1) * fov_tg2_x;
    double Y = -(2 * pixel_y / height - 1) * fov_tg2_y;
    return {position, glm::normalize(X * right + Y * up + forward)};

}

void Scene::init() {
    camera.init();
}

Color Scene::get_pixel_color(double_t pixel_x, double pixel_y) const {
    Ray ray = camera.get_ray(pixel_x, pixel_y);
    return get_color(ray);
}

Color Scene::get_color(const Ray &ray, uint8_t depth) const {
    if (depth == ray_depth) return bg_color;
    auto intersection_result = intersect_ray(ray);
    if (intersection_result.object_id == SceneIntersection::NO_OBJECT_ID) return bg_color;

    const auto &object = objects[intersection_result.object_id];
    static const double SHIFT = 1e-4;
    glm::dvec3 point = ray.o + ray.dir * intersection_result.object_intersection.t +
                      SHIFT * intersection_result.object_intersection.normal;

    Color color = object->color;

    switch (object->material) {
        case Material::DIFFUSE:
            return process_diffuse(color, point, intersection_result.object_intersection.normal);
        case Material::METALLIC:
            return process_metalic(color, point, intersection_result.object_intersection.normal, ray, depth);
        case Material::DIELECTRIC:
            return process_dielectric(intersection_result, ray, depth);
    }
}

SceneIntersection Scene::intersect_ray(const Ray &ray, double max_dist) const {
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

Color Scene::process_diffuse(const Color &color, const glm::dvec3 &point, const glm::dvec3 &normal) const {
    glm::dvec3 additional_color = ambient_light;
    for (const auto &light: lights) {
        double dist = light->get_distance(point);
        Ray to_light = {point, light->get_on_light_direction(point)};
        auto intersection = intersect_ray(to_light, dist);
        if (intersection.object_id == SceneIntersection::NO_OBJECT_ID) {
            additional_color += light->get_intensity(point) * std::max(0., glm::dot(to_light.dir, normal));
        }
    }

    return color * additional_color;
}

Color Scene::process_metalic(const Color &color, const glm::dvec3 &point, const glm::dvec3 &normal, const Ray &ray,
                             uint8_t depth) const {
    glm::dvec3 new_direction = ray.dir - 2. * normal * glm::dot(normal, ray.dir);
    Ray new_ray = {point, new_direction};
    return color * get_color(new_ray, depth + 1);
}

Color Scene::process_dielectric(const SceneIntersection &scene_intersection, const Ray &ray, uint8_t depth) const {
    auto &object = objects[scene_intersection.object_id];
    double n1 = 1;
    double n2 = object->index_of_reflection;
    if (scene_intersection.object_intersection.is_inside) std::swap(n1, n2);
    auto &normal = scene_intersection.object_intersection.normal;

    static const double SHIFT = 1e-4;
    glm::dvec3 shifted_forward_point = ray.o + ray.dir * scene_intersection.object_intersection.t -
                                      SHIFT * normal;
    glm::dvec3 shifted_back_point = ray.o + ray.dir * scene_intersection.object_intersection.t +
                                   SHIFT * normal;

    double cos_theta1 = glm::dot(-ray.dir, normal);
    double sin_theta2 = n1 / n2 * sqrt(1 - cos_theta1 * cos_theta1);

    glm::dvec3 reflected_direction = ray.dir - 2. * normal * glm::dot(normal, ray.dir);
    Ray reflected_ray = {shifted_back_point, reflected_direction};
    Color reflected_color = get_color(reflected_ray, depth + 1);

    if (sin_theta2 > 1) return reflected_color;

    double cos_theta2 = sqrt(1 - sin_theta2 * sin_theta2);
    glm::dvec3 refracted_direction = n1 / n2 * ray.dir + (n1 / n2 * cos_theta1 - cos_theta2) * normal;

    double R0 = (n1 - n2) * (n1 - n2) / (n1 + n2) / (n1 + n2);
    double reflection_factor = R0 + (1 - R0) * std::pow((1 - cos_theta1), 5);

    Ray refracted_ray = {shifted_forward_point, refracted_direction};
    Color refracted_color = get_color(refracted_ray, depth + 1);

    if (!scene_intersection.object_intersection.is_inside) refracted_color *= object->color;
    return reflection_factor * reflected_color + (1.f - reflection_factor) * refracted_color;
}
