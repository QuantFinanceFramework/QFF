#pragma once
#include "../AAD/aad_all.h"
#include "IInterestRateCurve.h"
namespace qff_a {
class IProduct {
 public:
  virtual ~IProduct() = default;

  template <typename T>
  T Evaluate(const IInterestRateCurve<T>& curve) const {
    return EvaluateImpl(curve);
  }

 private:
  virtual double EvaluateImpl(
      const IInterestRateCurve<double>& curve) const = 0;
  virtual aad::a_double EvaluateImpl(
      const IInterestRateCurve<aad::a_double>& curve) const = 0;
};
}  // namespace qff_a