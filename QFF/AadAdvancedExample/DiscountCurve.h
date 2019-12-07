#pragma once
#include <algorithm>
#include "../AAD/aad_all.h"
#include "ICurve.h"

template <typename T>
class DiscountCurve final : public ICurve<T> {
 public:
  DiscountCurve() = default;
  explicit DiscountCurve(std::vector<T> discount_factors)
      : discount_factors_(std::move(discount_factors)) {}

  T GetDiscountFactor(double time) const override;

  std::vector<double> GetAdjoints() const override;

 private:
  std::vector<T> discount_factors_;
};

template <typename T>
T DiscountCurve<T>::GetDiscountFactor(double time) const {
  if (time <= 1.0) return T(discount_factors_[0]);
  if (time <= 2.0) return T(discount_factors_[1]);
  if (time <= 3.0) return T(discount_factors_[2]);
}

template <typename T>
std::vector<double> DiscountCurve<T>::GetAdjoints() const {
  return std::vector<double>(size(discount_factors_));
}

template <>
inline std::vector<double> DiscountCurve<aad::aad_double>::GetAdjoints() const {
  std::vector<double> adjoints(size(discount_factors_));
  std::transform(discount_factors_.begin(), discount_factors_.end(),
                 adjoints.begin(), [](const auto& d) { return d.adjoint(); });
  return adjoints;
}
