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

  std::string GetCurrencyCode() const override { return currency_code_; }

  Currency<double> Evaluate(
      const IPricingEnvironment<double>& environment,
      const std::string& valuation_currency) const override {
    return EvaluateImpl(environment, valuation_currency);
  }

  Currency<aad::a_double> Evaluate(
      const IPricingEnvironment<aad::a_double>& environment,
      const std::string& valuation_currency) const override {
    return EvaluateImpl(environment, valuation_currency);
  }

 private:
  template <typename T>
  Currency<T> EvaluateImpl(const IPricingEnvironment<T>& environment,
                           const std::string& valuation_currency) const;

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

template <typename T>
Currency<T> FixedCashflow::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  if (IsExpired(environment)) {
    return Currency(valuation_currency, T(0.0));
  }
  auto npv =
      payment_amount_ *
      environment.GetDiscountFactor(GetDiscountCurveName(), GetPaymentDate()) *
      environment.GetFxToday(GetCurrencyCode(), valuation_currency);

  return Currency(valuation_currency, T(npv));
}
}  // namespace qff_a