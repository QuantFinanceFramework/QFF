#pragma once
#include <random>
#include "INormalRandomSequenceGenerator.h"

namespace qff {
class PseudoNormalRsg : public INormalRandomSequenceGenerator {
 public:
  PseudoNormalRsg() = default;
  PseudoNormalRsg(size_t dimension, unsigned int seed);
  explicit PseudoNormalRsg(size_t dimension);

  std::vector<double> GenerateNormalSequence() override;
  void SetDimension(size_t dimension) override;

 private:
  size_t dimension_;
  std::mt19937 rng_;
  std::normal_distribution<double> dist_;
};
}  // namespace qff