#ifndef HW1_PARSE_H
#define HW1_PARSE_H

#include <fstream>
#include <iostream>

#include "utils.hpp"
#include "Scene.h"
#include "Plane.h"
#include "Ellipsoid.h"
#include "Box.h"

uint8_t double_to_uint(double d);

Scene parse(const std::string &input_filename);

#endif //HW1_PARSE_H
