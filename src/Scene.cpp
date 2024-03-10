#include "Scene.h"

void Scene::Camera::init() {
    fov_tg2_y = fov_tg2_x * height / width;
}

Ray Scene::Camera::get_ray(double pixel_x, double pixel_y) const {
    double X = (2 * pixel_x / width - 1) * fov_tg2_x;
    double Y = -(2 * pixel_y / height - 1) * fov_tg2_y;
    return {position, glm::normalize(X * right + Y * up + forward)};

}

void Scene::init(std::vector<std::unique_ptr<Distribution>> &&light_distributions) {
    camera.init();
    if (!light_distributions.empty()) {
        std::vector<std::unique_ptr<Distribution>> final_dists;
        final_dists.emplace_back(std::make_unique<Cosine>());
        final_dists.emplace_back(std::make_unique<MixDistribution>(std::move(light_distributions)));
        sampler = std::make_unique<MixDistribution>(std::move(final_dists));
    } else {
        sampler = std::make_unique<Cosine>();
    }
}

Color Scene::get_pixel_color(uint32_t pixel_x, uint32_t pixel_y, RandomGenerator &rnd) const {
    Color color = {0, 0, 0};
    for (std::size_t _ = 0; _ < samples; _++) {
        Ray ray = camera.get_ray(pixel_x + rnd.get_random_float(), pixel_y + rnd.get_random_float());
        color += get_color(ray, rnd);
    }
    return color / static_cast<double>(samples);
}

glm::dvec3 shift_point(const Ray &ray, ObjectIntersection object_intersection, double shift) {
    return ray.o + ray.dir * object_intersection.t +
           shift * object_intersection.normal;
}

Color Scene::get_color(const Ray &ray, RandomGenerator &rnd, uint8_t depth) const {
    if (depth == ray_depth) return {0, 0, 0};
    auto intersection_result = intersect_ray(ray);
    if (intersection_result.object_id == SceneIntersection::NO_OBJECT_ID) return bg_color;

    const auto &object = objects[intersection_result.object_id];

    switch (object->material) {
        case Material::DIFFUSE:
            return process_diffuse(intersection_result, ray, depth, rnd);
        case Material::METALLIC:
            return process_metalic(intersection_result, ray, depth, rnd);
        case Material::DIELECTRIC:
            return process_dielectric(intersection_result, ray, depth, rnd);
        default:
            return {};
    }
}

SceneIntersection Scene::intersect_ray(const Ray &ray) const {
    SceneIntersection scene_intersection;
    scene_intersection.object_id = SceneIntersection::NO_OBJECT_ID;

    for (std::size_t i = 0; i < objects.size(); i++) {
        const auto &object = objects[i];
        auto result = object->intersect(ray);
        if (result.t < scene_intersection.object_intersection.t) {
            scene_intersection.object_intersection = result;
            scene_intersection.object_id = i;
        }
    }

    return scene_intersection;
}

Color Scene::get_reflected_color(const glm::dvec3 &point, const glm::dvec3 &normal, const Ray &ray,
                                 uint8_t depth, RandomGenerator &rnd) const {
    glm::dvec3 new_direction = ray.dir - 2. * normal * glm::dot(normal, ray.dir);
    Ray new_ray = {point, new_direction};
    return get_color(new_ray, rnd, depth + 1);
}

Color Scene::process_diffuse(const SceneIntersection &scene_intersection, const Ray &ray, uint8_t depth,
                             RandomGenerator &rnd) const {
    const auto &object = objects[scene_intersection.object_id];
    const auto &normal = scene_intersection.object_intersection.normal;
    auto point = shift_point(ray, scene_intersection.object_intersection, SHIFT);
    glm::dvec3 w;
    double pdf = 0;

    while (pdf == 0) {
        w = sampler->sample(point, normal, rnd);
        pdf = sampler->pdf(point, normal, w);
    }

    Ray new_ray = {point, w};
    auto dot = glm::dot(w, normal);

    auto res = object->emission + object->color * M_1_PI * get_color(new_ray, rnd, depth + 1) *
                                 dot / pdf;
    return res;
}

Color Scene::process_metalic(const SceneIntersection &scene_intersection, const Ray &ray,
                             uint8_t depth, RandomGenerator &rnd) const {
    auto &object = objects[scene_intersection.object_id];
    auto point = shift_point(ray, scene_intersection.object_intersection, SHIFT);
    return object->color * get_reflected_color(point, scene_intersection.object_intersection.normal, ray, depth, rnd);
}

Color Scene::process_dielectric(const SceneIntersection &scene_intersection, const Ray &ray, uint8_t depth,
                                RandomGenerator &rnd) const {
    auto &object = objects[scene_intersection.object_id];
    double n1 = 1;
    double n2 = object->index_of_reflection;
    if (scene_intersection.object_intersection.is_inside) std::swap(n1, n2);
    auto &normal = scene_intersection.object_intersection.normal;

    glm::dvec3 shifted_forward_point = shift_point(ray, scene_intersection.object_intersection, -SHIFT);
    glm::dvec3 shifted_back_point = shift_point(ray, scene_intersection.object_intersection, SHIFT);

    double cos_theta1 = glm::dot(-ray.dir, normal);
    double sin_theta2 = n1 / n2 * sqrt(1 - cos_theta1 * cos_theta1);

    if (sin_theta2 > 1) return get_reflected_color(shifted_back_point, normal, ray, depth, rnd);

    double cos_theta2 = sqrt(1 - sin_theta2 * sin_theta2);
    glm::dvec3 refracted_direction = n1 / n2 * ray.dir + (n1 / n2 * cos_theta1 - cos_theta2) * normal;

    double R0 = (n1 - n2) * (n1 - n2) / (n1 + n2) / (n1 + n2);
    double reflection_factor = R0 +
                               (1 - R0) * (1 - cos_theta1) * (1 - cos_theta1) * (1 - cos_theta1) * (1 - cos_theta1) *
                               (1 - cos_theta1);
    if (rnd.get_random_float() <= reflection_factor) {
        return get_reflected_color(shifted_back_point, normal, ray, depth, rnd);
    } else {
        Ray refracted_ray = {shifted_forward_point, refracted_direction};
        Color refracted_color = get_color(refracted_ray, rnd, depth + 1);

        if (!scene_intersection.object_intersection.is_inside) refracted_color *= object->color;
        return refracted_color;
    }
}
