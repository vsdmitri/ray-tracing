#ifndef HW1_PARSE_H
#define HW1_PARSE_H

#include <fstream>
#include <iostream>

#include "../src/ioUtils.hpp"
#include "Scene.h"
#include "Plane.h"
#include "Ellipsoid.h"
#include "Box.h"
#include "DirectionalLight.h"
#include "PointLight.h"

uint8_t double_to_uint(double d);

Scene parse(const std::string &input_filename);

#endif //HW1_PARSE_H
