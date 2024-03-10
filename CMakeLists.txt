cmake_minimum_required(VERSION 3.1)

project(ray-tracing)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -Werror -Wextra")

add_executable(ray-tracing
        src/main.cpp includes/ioUtils.hpp includes/simpleStructs.h src/Object/Object.cpp includes/Object/Object.h src/Object/Plane.cpp includes/Object/Plane.h src/Object/Ellipsoid.cpp includes/Object/Ellipsoid.h includes/Object/Box.h src/Object/Box.cpp src/parse.cpp includes/parse.h src/Scene.cpp includes/Scene.h src/Image.cpp includes/Image.h src/algebraUtils.cpp includes/algebraUtils.h src/RandomGenerator.cpp includes/RandomGenerator.h includes/geometryUtils.hpp src/Distributions/Cosine.cpp includes/Distributions/Cosine.h includes/Distributions/Distribution.h src/Distributions/BoxUniform.cpp includes/Distributions/BoxUniform.h src/Distributions/MixDistribution.cpp includes/Distributions/MixDistribution.h src/Distributions/EllipsoidDistribution.cpp includes/Distributions/EllipsoidDistribution.h src/Distributions/Distribution.cpp)

target_include_directories(
        ray-tracing PUBLIC glm
        ray-tracing PUBLIC includes
        ray-tracing PUBLIC includes/Object
        ray-tracing PUBLIC includes/Distributions
)