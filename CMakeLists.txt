cmake_minimum_required(VERSION 3.1)

project(ray-tracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(ray-tracing
        src/main.cpp src/ioUtils.hpp includes/simpleStructs.h src/Object/Object.cpp includes/Object/Object.h src/Object/Plane.cpp includes/Object/Plane.h src/Object/Ellipsoid.cpp includes/Object/Ellipsoid.h includes/Object/Box.h src/Object/Box.cpp src/parse.cpp includes/parse.h src/Scene.cpp includes/Scene.h src/Image.cpp includes/Image.h src/algebraUtils.cpp includes/algebraUtils.h includes/Light/Light.h src/Light/PointLight.cpp includes/Light/PointLight.h src/Light/DirectionalLight.cpp includes/Light/DirectionalLight.h)

target_include_directories(
        ray-tracing PUBLIC glm
        ray-tracing PUBLIC includes
        ray-tracing PUBLIC includes/Object
        ray-tracing PUBLIC includes/Light
)