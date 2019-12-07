#pragma once
#include "../AAD/aad_all.h"
#include "ICurve.h"

class Bond {
 public:
  template <typename T>
  T evaluate(const ICurve<T>& c) const;
};

template <typename T>
T Bond::evaluate(const ICurve<T>& c) const {
  return c.GetDiscountFactor(0) +
         c.GetDiscountFactor(1) * c.GetDiscountFactor(2);
}

template <>
inline aad::aad_double Bond::evaluate(const ICurve<aad::aad_double>& c) const {
  return aad::aad_double(c.GetDiscountFactor(0) +
                         c.GetDiscountFactor(1) * c.GetDiscountFactor(2));
}
