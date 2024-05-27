#include "parse.h"

Scene parse(const std::string &input_filename = "../in.txt") {
    std::ifstream in(input_filename);
    Scene scene;

    std::vector<std::unique_ptr<Distribution>> light_distributions;
    std::vector<std::shared_ptr<Object>> objects;

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
            double fov_x;
            s >> fov_x;
            scene.camera.fov_tg2_x = std::tan(fov_x / 2);
            continue;
        }

        if (command_name == "NEW_PRIMITIVE") {
            objects.emplace_back();
            continue;
        }

        if (command_name == "PLANE") {
            glm::dvec3 normal;
            s >> normal;
            objects.back() = std::make_shared<Plane>(normal);
            continue;
        }

        if (command_name == "ELLIPSOID") {
            glm::dvec3 rs;
            s >> rs;
            objects.back() = std::make_shared<Ellipsoid>(rs);
            continue;
        }

        if (command_name == "BOX") {
            glm::dvec3 ss;
            s >> ss;
            objects.back() = std::make_shared<Box>(ss);
            continue;
        }

        if (command_name == "TRIANGLE") {
            glm::dvec3 a, b, c;
            s >> a >> b >> c;
            objects.back() = std::make_shared<Triangle>(a, b, c);
            continue;
        }

        if (command_name == "POSITION") {
            s >> objects.back()->position;
            continue;
        }

        if (command_name == "ROTATION") {
            s >> objects.back()->rotation;
            objects.back()->inverse_rotation = glm::conjugate(objects.back()->rotation);
            continue;
        }

        if (command_name == "COLOR") {
            s >> objects.back()->color;
            continue;
        }

        if (command_name == "RAY_DEPTH") {
            int depth;
            s >> depth;
            scene.ray_depth = depth;
            continue;
        }

        if (command_name == "SAMPLES") {
            s >> scene.samples;
            continue;
        }

        if (command_name == "EMISSION") {
            s >> objects.back()->emission;
            switch (objects.back()->getTag()) {
                case ObjectTag::Box: {
                    auto ptr = std::dynamic_pointer_cast<Box>(objects.back());
                    light_distributions.push_back(std::make_unique<BoxUniform>(ptr));
                    break;
                }
                case ObjectTag::Ellipsoid: {
                    auto ptr = std::dynamic_pointer_cast<Ellipsoid>(objects.back());
                    light_distributions.push_back(std::make_unique<EllipsoidDistribution>(ptr));
                    break;
                }
                case ObjectTag::Triangle: {
                    auto ptr = std::dynamic_pointer_cast<Triangle>(objects.back());
                    light_distributions.push_back(std::make_unique<TriangleDistribution>(ptr));
                    break;
                }
                case ObjectTag::Plane:
                    break;
            }
            continue;
        }

        if (command_name == "METALLIC") {
            objects.back()->material = Material::METALLIC;
            continue;
        }

        if (command_name == "DIELECTRIC") {
            objects.back()->material = Material::DIELECTRIC;
            continue;
        }

        if (command_name == "IOR") {
            s >> objects.back()->index_of_refraction;
            continue;
        }

        if (command_name.empty()) continue;

        std::cerr << "Unexpected command: " << command_name << "\n";
    }

    scene.init(std::move(light_distributions), std::move(objects));
    return scene;
}