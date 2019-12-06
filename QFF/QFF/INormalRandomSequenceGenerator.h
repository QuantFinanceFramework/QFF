#pragma once
#include <vector>

namespace qff {

class INormalRandomSequenceGenerator {
 public:
  virtual ~INormalRandomSequenceGenerator() = default;

  virtual std::vector<double> GenerateNormalSequence() = 0;
  virtual void SetDimension(size_t dimension) = 0;
};
}  // namespace qff