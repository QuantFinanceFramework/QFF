#pragma once
#include "../AAD/aad_all.h"
#include "ICurve.h"

template <typename T>
class ParametricCurve final : public ICurve<T> {
 public:
  ParametricCurve() = default;
  ParametricCurve(T m, T c) : m_{m}, c_{c} {};

  T GetDiscountFactor(double time) const override;

  std::vector<double> GetAdjoints() const override;

 private:
  T m_;
  T c_;
};

template <typename T>
T ParametricCurve<T>::GetDiscountFactor(double time) const {
  return T(m_ * time + c_);
}

template <typename T>
std::vector<double> ParametricCurve<T>::GetAdjoints() const {
  return std::vector<double>(2);
}

template <>
inline std::vector<double> ParametricCurve<aad::a_double>::GetAdjoints() const {
  return std::vector<double>{m_.adjoint(), c_.adjoint()};
}
