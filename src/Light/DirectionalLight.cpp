#include "DirectionalLight.h"

glm::vec3 DirectionalLight::get_intensity(const glm::vec3 &point) const {
    return intensity;
}

glm::vec3 DirectionalLight::get_on_light_direction(const glm::vec3 &point) const {
    return direction;
}

float DirectionalLight::get_distance(const glm::vec3 &point) const {
    return std::numeric_limits<float>::max();
}
