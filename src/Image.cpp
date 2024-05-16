#include "Image.h"

glm::dvec3 saturate(const glm::dvec3 &color) {
    return glm::clamp(color, glm::dvec3(0.0), glm::dvec3(1.0));
}

glm::dvec3 aces_tonemap(const glm::dvec3 &x) {
    const double a = 2.51f;
    const double b = 0.03f;
    const double c = 2.43f;
    const double d = 0.59f;
    const double e = 0.14f;
    return saturate((x * (a * x + b)) / (x * (c * x + d) + e));
}

uint8_t float_to_uint(double d) {
    return round(255 * d);
}

Image::Pixel prepare_color(Color color) {
    static const double GAMMA = 2.2f, INVERSE_GAMMA = 1 / GAMMA;
    color = aces_tonemap(color);
    for (std::size_t i = 0; i < 3; i++) {
        color[i] = std::pow(color[i], INVERSE_GAMMA);
    }
    return {float_to_uint(color.x), float_to_uint(color.y), float_to_uint(color.z)};
}

void Image::set_color(uint32_t j, uint32_t i, const Color &color) {
    pixels_[j * width_ + i] = prepare_color(color);
}

void Image::save(const std::string &output_filename) {
    std::ofstream out(output_filename, std::ios::binary);
    out << "P6" << std::endl << width_ << " " << height_ << std::endl << "255" << std::endl;
    out.write(reinterpret_cast<char *>(pixels_.data()), width_ * height_ * 3);
}
