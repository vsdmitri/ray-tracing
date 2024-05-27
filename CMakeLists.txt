cmake_minimum_required(VERSION 3.1)

project(ray-tracing)

set(CMAKE_CXX_STANDARD 20)

OPTION(USE_OpenMP "Use OpenMP to enable <omp.h>" ON)

# Find OpenMP
if (APPLE AND USE_OpenMP)
    if (CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(OpenMP_C "${CMAKE_C_COMPILER}")
        set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
        set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
        set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
        set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
        set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
    endif ()
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
        set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
        set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
        set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
        set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
        set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})
    endif ()
endif ()

if (USE_OpenMP)
    find_package(OpenMP REQUIRED)
endif (USE_OpenMP)

if (OPENMP_FOUND)
    link_directories("${OPENMP_LIBRARIES}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif (OPENMP_FOUND)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -Werror -Wextra")

add_executable(ray-tracing
        src/main.cpp includes/ioUtils.hpp includes/simpleStructs.h src/Object/Object.cpp includes/Object/Object.h src/Object/Plane.cpp includes/Object/Plane.h src/Object/Ellipsoid.cpp includes/Object/Ellipsoid.h includes/Object/Box.h src/Object/Box.cpp src/parse.cpp includes/parse.h src/Scene.cpp includes/Scene.h src/Image.cpp includes/Image.h includes/algebraUtils.h src/RandomGenerator.cpp includes/RandomGenerator.h includes/geometryUtils.hpp src/Distributions/Cosine.cpp includes/Distributions/Cosine.h includes/Distributions/Distribution.h src/Distributions/BoxUniform.cpp includes/Distributions/BoxUniform.h src/Distributions/MixDistribution.cpp includes/Distributions/MixDistribution.h src/Distributions/EllipsoidDistribution.cpp includes/Distributions/EllipsoidDistribution.h src/Distributions/Distribution.cpp src/Object/Triangle.cpp includes/Object/Triangle.h src/Distributions/TriangleDistribution.cpp includes/Distributions/TriangleDistribution.h src/AABB.cpp includes/AABB.h src/BVH.cpp includes/BVH.h)

target_include_directories(
        ray-tracing PUBLIC glm
        ray-tracing PUBLIC includes
        ray-tracing PUBLIC includes/Object
        ray-tracing PUBLIC includes/Distributions
)