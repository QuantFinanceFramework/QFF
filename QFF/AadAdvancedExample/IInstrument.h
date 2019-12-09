#pragma once
#include "../AAD/aad_all.h"
#include "ICurve.h"

class IInstrument {
 public:
  virtual ~IInstrument() = default;

  template <typename T>
  T Evaluate(const ICurve<T>& curve) const {
    return EvaluateImpl(curve);
  }

 private:
  virtual double EvaluateImpl(const ICurve<double>& curve) const = 0;
  virtual aad::aad_double EvaluateImpl(
      const ICurve<aad::aad_double>& curve) const = 0;
};