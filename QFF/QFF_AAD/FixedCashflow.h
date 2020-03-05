#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>

#include "ICashflow.h"

namespace qff_a {
class FixedCashflow final : public ICashflow {
 public:
  FixedCashflow(double payment_amount, boost::gregorian::date payment_date,
                std::string discount_curve_name);

  boost::gregorian::date GetPaymentDate() const override {
    return payment_date_;
  }

  std::string GetDiscountCurveName() const override {
    return discount_curve_name_;
  }

  double GetPaymentAmount(
      const IPricingEnvironment<double>& environment) const override {
    return GetPaymentAmountImpl(environment);
  }

  aad::a_double GetPaymentAmount(
      const IPricingEnvironment<aad::a_double>& environment) const override {
    return GetPaymentAmountImpl(environment);
  }

 private:
  template <typename T>
  T GetPaymentAmountImpl(const IPricingEnvironment<T>& environment) const;

  double payment_amount_{};
  boost::gregorian::date payment_date_;
  std::string discount_curve_name_;
};

inline FixedCashflow::FixedCashflow(double payment_amount,
                                    boost::gregorian::date payment_date,
                                    std::string discount_curve_name)
    : payment_amount_{payment_amount},
      payment_date_{payment_date},
      discount_curve_name_(std::move(discount_curve_name)) {}

template <typename T>
T FixedCashflow::GetPaymentAmountImpl(
    const IPricingEnvironment<T>& environment) const {
  return T(payment_amount_);
}
}  // namespace qff_a