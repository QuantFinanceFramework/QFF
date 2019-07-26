#pragma once
#include <vector>

namespace qff {
using std::vector;

class INormalRandomSequenceGenerator {
 public:
  INormalRandomSequenceGenerator() = default;
  virtual ~INormalRandomSequenceGenerator() = default;

  virtual vector<double> GenerateNormalSequence() = 0;
  virtual void SetDimension(size_t dimension) = 0;
};
}  // namespace qff