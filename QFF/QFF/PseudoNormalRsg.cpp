#include "PseudoNormalRsg.h"

using std::vector;

namespace qff {
PseudoNormalRsg::PseudoNormalRsg(size_t dimension, unsigned int seed)
    : dimension_{dimension},
      rng_{std::mt19937{seed}},
      dist_{std::normal_distribution<double>{0, 1}} {}

PseudoNormalRsg::PseudoNormalRsg(size_t dimension)
    : dimension_{dimension}, rng_{std::mt19937{std::random_device{}()}} {}

vector<double> PseudoNormalRsg::GenerateNormalSequence() {
  vector<double> result(dimension_);
  for (auto& i : result) {
    i = dist_(rng_);
  }

  return result;
}

void PseudoNormalRsg::SetDimension(size_t dimension) {
  dimension_ = dimension;
}
}  // namespace qff