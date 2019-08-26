#pragma once
#include <random>
#include "INormalRandomSequenceGenerator.h"

namespace qff {
class PseudoNormalRsg : public INormalRandomSequenceGenerator {
 public:
  PseudoNormalRsg(size_t dimension, unsigned int seed);
  PseudoNormalRsg(size_t dimension);
  ~PseudoNormalRsg() = default;

  std::vector<double> GenerateNormalSequence() override;
  void SetDimension(size_t dimension) override;

 private:
  size_t dimension_;
  std::mt19937 rng_;
  std::normal_distribution<double> dist_;
};
}  // namespace qff