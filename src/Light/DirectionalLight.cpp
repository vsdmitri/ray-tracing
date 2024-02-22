#include "DirectionalLight.h"

glm::dvec3 DirectionalLight::get_intensity(const glm::dvec3 &point) const {
    return intensity;
}

glm::dvec3 DirectionalLight::get_on_light_direction(const glm::dvec3 &point) const {
    return direction;
}

double DirectionalLight::get_distance(const glm::dvec3 &point) const {
    return std::numeric_limits<double>::max();
}
