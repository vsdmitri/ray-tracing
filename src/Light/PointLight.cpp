#include "PointLight.h"

glm::dvec3 PointLight::get_intensity(const glm::dvec3 &point) const {
    double dist = glm::length(point - position);
    return intensity / glm::dot(attenuation, {1, dist, dist * dist});
}

void PointLight::set_attenuation(const glm::dvec3 &attenuation_new) {
    attenuation = attenuation_new;
}

glm::dvec3 PointLight::get_on_light_direction(const glm::dvec3 &point) const {
    return glm::normalize(position - point);
}

double PointLight::get_distance(const glm::dvec3 &point) const {
    return glm::length(point - position);
}


