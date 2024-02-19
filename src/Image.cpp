#include "Image.h"

void Image::set_color(uint32_t j, uint32_t i, const Color &color) {
    pixels[j * width + i] = color;
}

void Image::save(const std::string &output_filename) {
    std::ofstream out(output_filename);
    out << "P6\n" << width << " " << height << "\n255\n";
    auto *data = reinterpret_cast<uint8_t *>(pixels.data());
    for (std::size_t i = 0; i < width * height * 3; i++) {
        out << data[i];
    }
}
