#pragma once
#include <string>
#include <vector>

namespace qff_a {
class IrDeltas {
 public:
  void Append(IrDeltas rhs);
  void PrintDeltas() const;
  IrDeltas() = default;
  IrDeltas(std::vector<std::string> pillars, std::vector<double> deltas);

 private:
  std::vector<std::string> pillars_;
  std::vector<double> deltas_;
};
}  // namespace qff_a
