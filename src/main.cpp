#include <thread>
#include <vector>

#include "Scene.h"
#include "parse.h"
#include "Image.h"
#include "RandomGenerator.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "error: no input_path or output_path";
        exit(1);
    }

    Scene scene = parse(argv[1]);
    Image img(scene.camera.width, scene.camera.height);
    RandomGenerator r;
    for (std::size_t i = 0; i < scene.camera.width; i++) {
        for (std::size_t j = 0; j < scene.camera.height; j++) {
            img.set_color(j, i, scene.get_pixel_color(i, j, r));
        }
    }

    img.save(argv[2]);
    return 0;
}
