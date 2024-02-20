#ifndef HW1_IMAGE_H
#define HW1_IMAGE_H

#include <vector>
#include <fstream>

#include "common.hpp"
#include "gtc/color_space.hpp"

#include "simpleStructs.h"

struct Image {
    Image(uint32_t width, uint32_t height) : width(width), height(height), pixels(width * height) {}

    struct Pixel {
        uint8_t r, g, b;
    };

    uint32_t width, height;
    std::vector<Pixel> pixels;

    void set_color(uint32_t j, uint32_t i, const Color& color);

    void save(const std::string &output_filename);
};


#endif //HW1_IMAGE_H
