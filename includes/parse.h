#ifndef HW1_PARSE_H
#define HW1_PARSE_H

#include <fstream>
#include <iostream>

#include "ioUtils.hpp"
#include "Scene.h"
#include "Plane.h"
#include "Ellipsoid.h"
#include "Box.h"

Scene parse(const std::string &input_filename);

#endif //HW1_PARSE_H
