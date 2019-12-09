#pragma once
#include <vector>
#include "IInstrument.h"

class ConcreteInstrument final : public IInstrument {
 public:
  ConcreteInstrument() = default;
  ConcreteInstrument(double notional, std::vector<double> payment_times)
      : notional_{notional}, payment_times_{std::move(payment_times)} {};

 private:
  double EvaluateImpl(const ICurve<double>& curve) const override;
  aad::a_double EvaluateImpl(
      const ICurve<aad::a_double>& curve) const override;

  double notional_{};
  std::vector<double> payment_times_{};
};
