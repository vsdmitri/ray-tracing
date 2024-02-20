#include "Image.h"

glm::vec3 saturate(const glm::vec3 &color) {
    return glm::clamp(color, glm::vec3(0.0), glm::vec3(1.0));
}

glm::vec3 aces_tonemap(const glm::vec3 &x) {
    const float a = 2.51f;
    const float b = 0.03f;
    const float c = 2.43f;
    const float d = 0.59f;
    const float e = 0.14f;
    return saturate((x * (a * x + b)) / (x * (c * x + d) + e));
}

uint8_t float_to_uint(float d) {
    return round(255 * d);
}

Image::Pixel prepare_color(Color color) {
    static const float GAMMA = 2.2f, INVERSE_GAMMA = 1 / GAMMA;
    color = aces_tonemap(color);
    for (std::size_t i = 0; i < 3; i++) {
        color[i] = std::pow(color[i], INVERSE_GAMMA);
    }
    return {float_to_uint(color.x), float_to_uint(color.y), float_to_uint(color.z)};
}

void Image::set_color(uint32_t j, uint32_t i, const Color &color) {
    pixels[j * width + i] = prepare_color(color);
}

void Image::save(const std::string &output_filename) {
    std::ofstream out(output_filename);
    out << "P6\n" << width << " " << height << "\n255\n";
    auto *data = reinterpret_cast<uint8_t *>(pixels.data());
    for (std::size_t i = 0; i < width * height * 3; i++) {
        out << data[i];
    }
}
