#include "ConcreteInstrument.h"
#include <numeric>

double ConcreteInstrument::EvaluateImpl(const ICurve<double>& curve) const {
  return notional_ *
         std::transform_reduce(
             payment_times_.begin(), payment_times_.end(), 0.0, std::plus(),
             [&](auto time) { return curve.GetDiscountFactor(time); });
}

aad::aad_double ConcreteInstrument::EvaluateImpl(
    const ICurve<aad::aad_double>& curve) const {
  return aad::aad_double(
      notional_ *
      std::transform_reduce(payment_times_.begin(), payment_times_.end(),
                            aad::aad_double(0.0), std::plus(), [&](auto time) {
                              return curve.GetDiscountFactor(time);
                            }));
}
