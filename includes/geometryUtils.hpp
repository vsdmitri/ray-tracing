#include "glm.hpp"

template<class T>
void fast_rotate(const glm::qua<T> &q, glm::vec3 &v) {
    glm::vec3 t = 2.f * glm::cross({q[1], q[2], q[3]}, v);
    v = v + q[0] * t + cross({q[1], q[2], q[3]}, t);
}