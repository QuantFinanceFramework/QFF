#pragma once
#include "Currency.h"
#include "IrDeltas.h"

namespace qff_a {
class IrResult {
 public:
  IrResult(Currency<double> npv, IrDeltas deltas);
  double GetNpv() const;
  std::string GetResultCurrency() const;
  IrDeltas GetIrDeltas() const;
  void PrintDeltas() const;

 private:
  const Currency<double> npv_;
  const IrDeltas deltas_;
};
}  // namespace qff_a