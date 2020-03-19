#pragma once
#include <boost/date_time/gregorian/gregorian.hpp>

#include "ICashflow.h"

namespace qff_a {
class FixedCashflow final : public ICashflow {
 public:
  FixedCashflow(double payment_amount, std::string currency_code,
                boost::gregorian::date payment_date,
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

  std::string GetCurrencyCode() const override;

 private:
  template <typename T>
  T GetPaymentAmountImpl(const IPricingEnvironment<T>& environment) const;

  double payment_amount_{};
  std::string currency_code_;
  boost::gregorian::date payment_date_;
  std::string discount_curve_name_;
};

inline FixedCashflow::FixedCashflow(double payment_amount,
                                    std::string currency_code,
                                    boost::gregorian::date payment_date,
                                    std::string discount_curve_name)
    : payment_amount_{payment_amount},
      currency_code_{std::move(currency_code)},
      payment_date_{payment_date},
      discount_curve_name_(std::move(discount_curve_name)) {}

inline std::string FixedCashflow::GetCurrencyCode() const {
  return currency_code_;
}

template <typename T>
T FixedCashflow::GetPaymentAmountImpl(
    const IPricingEnvironment<T>& environment) const {
  return T(payment_amount_);
}
}  // namespace qff_a