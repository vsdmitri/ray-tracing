#include "MixDistribution.h"

glm::dvec3 MixDistribution::sample(const glm::dvec3 &x, const glm::dvec3 &n, RandomGenerator &r, bool regen) const {
    if (!regen) {
        last_id_ = r.get_random_uint(dists_.size());
    }
    return dists_[last_id_]->sample(x, n, r);
}

double MixDistribution::pdf(const glm::dvec3 &x, const glm::dvec3 &n, const glm::dvec3 &d) const {
    double res = 0;
    for (const auto &el: dists_) {
        res += el->pdf(x, n, d);
    }
    return res / dists_.size();
}
