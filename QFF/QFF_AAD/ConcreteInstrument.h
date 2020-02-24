#pragma once
#include <vector>
#include <numeric>

#include "IProduct.h"
namespace qff_a {
class ConcreteInstrument final : public IProduct {
 public:
  ConcreteInstrument() = default;
  ConcreteInstrument(double notional, std::vector<double> payment_times)
      : notional_{notional}, payment_times_{std::move(payment_times)} {};

 private:
  double EvaluateImpl(const IInterestRateCurve<double>& curve) const override {
    return EvaluateImpl<double>(curve);
  }
  aad::a_double EvaluateImpl(
      const IInterestRateCurve<aad::a_double>& curve) const override {
    return EvaluateImpl<aad::a_double>(curve);
  }

  template <typename T>
  T EvaluateImpl(const IInterestRateCurve<T>& curve) const;

  double notional_{};
  std::vector<double> payment_times_{};
};

template <typename T>
T ConcreteInstrument::EvaluateImpl(const IInterestRateCurve<T>& curve) const {
  return T(notional_ *
           std::transform_reduce(payment_times_.begin(), payment_times_.end(),
                                 T(0.0), std::plus(), [&](auto time) {
                                   return curve.GetDiscountFactor(time);
                                 }));
}
}  // namespace qff_a