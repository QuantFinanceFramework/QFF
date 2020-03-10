#pragma once
#include "IrDeltas.h"

namespace qff_a {
class IrResult {
 public:
  IrResult(double npv, IrDeltas deltas);
  double GetNpv() const;
  IrDeltas GetIrDeltas() const;
  void PrintDeltas() const;

 private:
  const double npv_{};
  const IrDeltas deltas_;
};
}  // namespace qff_a