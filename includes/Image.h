#ifndef HW1_IMAGE_H
#define HW1_IMAGE_H

#include <vector>
#include <fstream>

#include "common.hpp"
#include "gtc/color_space.hpp"

#include "simpleStructs.h"

struct Image {
    Image(uint32_t width, uint32_t height) : width_(width), height_(height), pixels_(width * height) {}

    struct Pixel {
        uint8_t r, g, b;
    };

    uint32_t width_, height_;
    std::vector<Pixel> pixels_;

    void set_color(uint32_t j, uint32_t i, const Color& color);

    void save(const std::string &output_filename);
};


#endif //HW1_IMAGE_H
