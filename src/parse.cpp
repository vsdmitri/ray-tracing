#include "parse.h"

Scene parse(const std::string &input_filename = "../in.txt") {
    std::ifstream in(input_filename);
    Scene scene;
    for (std::string line; std::getline(in, line);) {
        std::stringstream s(line);
        std::string command_name;
        s >> command_name;

        if (command_name == "DIMENSIONS") {
            s >> scene.camera.width >> scene.camera.height;
            continue;
        }

        if (command_name == "BG_COLOR") {
            s >> scene.bg_color;
            continue;
        }

        if (command_name == "CAMERA_POSITION") {
            s >> scene.camera.position;
            continue;
        }

        if (command_name == "CAMERA_RIGHT") {
            s >> scene.camera.right;
            continue;
        }

        if (command_name == "CAMERA_UP") {
            s >> scene.camera.up;
            continue;
        }

        if (command_name == "CAMERA_FORWARD") {
            s >> scene.camera.forward;
            continue;
        }

        if (command_name == "CAMERA_FOV_X") {
            float fov_x;
            s >> fov_x;
            scene.camera.fov_tg2_x = std::tan(fov_x / 2);
            continue;
        }

        if (command_name == "NEW_PRIMITIVE") {
            scene.objects.emplace_back();
            continue;
        }

        if (command_name == "PLANE") {
            glm::vec3 normal;
            s >> normal;
            scene.objects.back() = std::make_unique<Plane>(normal);
            continue;
        }

        if (command_name == "ELLIPSOID") {
            glm::vec3 rs;
            s >> rs;
            scene.objects.back() = std::make_unique<Ellipsoid>(rs);
            continue;
        }

        if (command_name == "BOX") {
            glm::vec3 ss;
            s >> ss;
            scene.objects.back() = std::make_unique<Box>(ss);
            continue;
        }

        if (command_name == "POSITION") {
            s >> scene.objects.back()->position;
            continue;
        }

        if (command_name == "ROTATION") {
            s >> scene.objects.back()->rotation;
            scene.objects.back()->inverse_rotation = glm::conjugate(scene.objects.back()->rotation);
            continue;
        }

        if (command_name == "COLOR") {
            s >> scene.objects.back()->color;
            continue;
        }

        if (command_name == "RAY_DEPTH") {
            s >> scene.ray_depth;
            continue;
        }

        if (command_name == "AMBIENT_LIGHT") {
            s >> scene.ambient_light;
            continue;
        }

        if (command_name == "NEW_LIGHT") {
            scene.lights.emplace_back();
            continue;
        }

        if (command_name == "LIGHT_DIRECTION") {
            glm::vec3 direction;
            s >> direction;
            scene.lights.back() = std::make_unique<DirectionalLight>(direction);
            continue;
        }

        if (command_name == "LIGHT_POSITION") {
            glm::vec3 position;
            s >> position;
            scene.lights.back() = std::make_unique<PointLight>(position);
            continue;
        }

        if (command_name == "LIGHT_INTENSITY") {
            s >> scene.lights.back()->intensity;
            continue;
        }

        if (command_name == "LIGHT_ATTENUATION") {
            glm::vec3 attenuation;
            // TODO ?
            s >> attenuation;
            dynamic_cast<PointLight *>(scene.lights.back().get())->set_attenuation(attenuation);
            continue;
        }

        if (command_name.empty()) continue;

        std::cerr << "Unexpected command: " << command_name << "\n";
    }

    scene.init();
    return scene;
}