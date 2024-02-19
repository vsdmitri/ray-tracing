#ifndef HW1_IMAGE_H
#define HW1_IMAGE_H

#include <vector>
#include <fstream>

#include "simpleStructs.h"

struct Image {
    Image(uint32_t width, uint32_t height) : width(width), height(height), pixels(width * height) {}

    uint32_t width, height;
    std::vector<Color> pixels;

    void set_color(uint32_t i, uint32_t j, const Color& color);
    void save(const std::string &output_filename);
};



#endif //HW1_IMAGE_H
