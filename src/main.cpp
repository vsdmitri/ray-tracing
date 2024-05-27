#include <chrono>

#include <omp.h>

#include "Scene.h"
#include "parse.h"
#include "Image.h"
#include "RandomGenerator.h"

int main(int argc, char **argv) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    if (argc < 2) {
        std::cerr << "error: no input_path or output_path";
        exit(1);
    }

    Scene scene = parse(argv[1]);
    Image img(scene.camera.width, scene.camera.height);

#pragma omp parallel for
    for (std::size_t i = 0; i < scene.camera.width; i++) {
        RandomGenerator r;
        for (std::size_t j = 0; j < scene.camera.height; j++) {
            img.set_color(j, i, scene.get_pixel_color(i, j, r));
        }
    }

    img.save(argv[2]);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << (end - begin).count() / 1e9 << '\n';
    return 0;
}
