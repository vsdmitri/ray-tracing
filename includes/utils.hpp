#include <cmath>
#include <sstream>
#include "vec3.hpp"

template<glm::length_t L, typename T>
std::stringstream &operator>>(std::stringstream &in, glm::vec<L, T> &v) {
    for (std::size_t i = 0; i < L; i++) {
        in >> v[i];
    }
    return in;
}

template<typename T>
std::stringstream &operator>>(std::stringstream &in, glm::qua<T> &q) {
    in >> q[1] >> q[2] >> q[3] >> q[0];
    return in;
}