#include "PointLight.h"

glm::vec3 PointLight::get_intensity(const glm::vec3 &point) const {
    float dist = glm::length(point - position);
    return intensity / glm::dot(attenuation, {1, dist, dist * dist});
}

void PointLight::set_attenuation(const glm::vec3 &attenuation_new) {
    attenuation = attenuation_new;
}

glm::vec3 PointLight::get_on_light_direction(const glm::vec3 &point) const {
    return glm::normalize(position - point);
}

float PointLight::get_distance(const glm::vec3 &point) const {
    return glm::length(point - position);
}


