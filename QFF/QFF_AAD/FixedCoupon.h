#pragma once
#include <memory>

#include "ICashflow.h"
#include "IDayCounter.h"

namespace qff_a {
class FixedCoupon final : public ICashflow {
 public:
  FixedCoupon(double notional, std::string currency_code,
              boost::gregorian::date accrual_start_date,
              boost::gregorian::date accrual_end_date,
              boost::gregorian::date payment_date,
              std::string discount_curve_name, const IDayCounter& day_counter,
              double rate);

  boost::gregorian::date GetPaymentDate() const override {
    return payment_date_;
  }

  std::string GetDiscountCurveName() const override {
    return discount_curve_name_;
  }
  std::string GetCurrencyCode() const override { return currency_code_; }

  template <typename T>
  T GetScaledBasisPointValue(const IPricingEnvironment<T>& environment) const;

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
  double notional_{};
  std::string currency_code_;
  boost::gregorian::date accrual_start_date_;
  boost::gregorian::date accrual_end_date_;
  double accrual_factor_{};
  boost::gregorian::date payment_date_;
  std::string discount_curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
  double rate_{};
};

inline FixedCoupon::FixedCoupon(double notional, std::string currency_code,
                                boost::gregorian::date accrual_start_date,
                                boost::gregorian::date accrual_end_date,
                                boost::gregorian::date payment_date,
                                std::string discount_curve_name,
                                const IDayCounter& day_counter, double rate)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      accrual_start_date_(accrual_start_date),
      accrual_end_date_(accrual_end_date),
      accrual_factor_(day_counter.CalculateYearFraction(accrual_start_date,
                                                        accrual_end_date)),
      payment_date_(payment_date),
      discount_curve_name_(std::move(discount_curve_name)),
      day_counter_(day_counter.Clone()),
      rate_(rate) {}

template <typename T>
T FixedCoupon::GetScaledBasisPointValue(
    const IPricingEnvironment<T>& environment) const {
  return T(
      notional_ * accrual_factor_ *
      environment.GetDiscountFactor(GetDiscountCurveName(), GetPaymentDate()));
}

template <typename T>
Currency<T> FixedCoupon::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  auto npv = rate_ * GetScaledBasisPointValue(environment) *
             environment.GetFxToday(GetCurrencyCode(), valuation_currency);

  return Currency(valuation_currency, T(npv));
}
}  // namespace qff_a