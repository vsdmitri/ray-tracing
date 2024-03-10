#include "MixDistribution.h"

glm::dvec3 MixDistribution::sample(const glm::dvec3 &x, const glm::dvec3 &n, RandomGenerator &r) const {
    uint32_t index = r.get_random_uint(dists_.size());
    return dists_[index]->sample(x, n, r);
}

double MixDistribution::pdf(const glm::dvec3 &x, const glm::dvec3 &n, const glm::dvec3 &d) const {
    double res = 0;
    for (const auto &el: dists_) {
        res += el->pdf(x, n, d);
    }
    return res / dists_.size();
}
