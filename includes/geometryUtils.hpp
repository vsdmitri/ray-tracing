#include "glm.hpp"

template<class T>
void fast_rotate(const glm::qua<T> &q, glm::dvec3 &v) {
    glm::dvec3 t = 2. * glm::cross({q[1], q[2], q[3]}, v);
    v = v + q[0] * t + cross({q[1], q[2], q[3]}, t);
}