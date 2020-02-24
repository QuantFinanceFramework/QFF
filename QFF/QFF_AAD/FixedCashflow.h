#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>

#include "IProduct.h"
namespace qff_a {
class FixedCashflow final : public IProduct {
 public:
  FixedCashflow() = default;
  FixedCashflow(double payment_amount, boost::gregorian::date payment_date)
      : payment_amount_{payment_amount}, payment_date_{payment_date} {};

 private:
  double EvaluateImpl(const IInterestRateCurve<double>& curve) const final {
    return EvaluateImpl<double>(curve);
  }
  aad::a_double EvaluateImpl(
      const IInterestRateCurve<aad::a_double>& curve) const final {
    return EvaluateImpl<aad::a_double>(curve);
  }

  template <typename T>
  T EvaluateImpl(const IInterestRateCurve<T>& curve) const;

  double payment_amount_{};
  boost::gregorian::date payment_date_;
};

template <typename T>
T FixedCashflow::EvaluateImpl(const IInterestRateCurve<T>& curve) const {
  return T(payment_amount_ * curve.GetDiscountFactor(payment_date_));
}
}  // namespace qff_a