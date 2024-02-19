#include "Scene.h"
#include "parse.h"
#include "Image.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "error: no input_path or output_path";
        exit(1);
    }

    Scene scene = parse(argv[1]);
    Image img(scene.camera.width, scene.camera.height);

    for (std::size_t i = 0; i < scene.camera.width; i++) {
        for (std::size_t j = 0; j < scene.camera.height; j++) {
            img.set_color(j, i, scene.intersect_ray(i + 0.5f, j + 0.5f));
        }
    }

    img.save(argv[2]);
    return 0;
}
