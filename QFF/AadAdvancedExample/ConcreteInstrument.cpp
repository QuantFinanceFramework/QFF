#include "ConcreteInstrument.h"
#include <numeric>

double ConcreteInstrument::EvaluateImpl(const ICurve<double>& curve) const {
  return notional_ *
         std::transform_reduce(
             payment_times_.begin(), payment_times_.end(), 0.0, std::plus(),
             [&](auto time) { return curve.GetDiscountFactor(time); });
}

aad::a_double ConcreteInstrument::EvaluateImpl(
    const ICurve<aad::a_double>& curve) const {
  return aad::a_double(
      notional_ *
      std::transform_reduce(payment_times_.begin(), payment_times_.end(),
                            aad::a_double(0.0), std::plus(), [&](auto time) {
                              return curve.GetDiscountFactor(time);
                            }));
}
