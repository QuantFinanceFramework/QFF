#pragma once
#include <memory>

#include "ICashflow.h"
#include "IDayCounter.h"

namespace qff_a {
class CdsPremium final : public ICashflow {
 public:
  CdsPremium(double notional, std::string currency_code,
             boost::gregorian::date accrual_start_date,
             boost::gregorian::date accrual_end_date,
             boost::gregorian::date payment_date,
             std::string discount_curve_name, std::string survival_curve_name,
             const IDayCounter& day_counter, double cds_spread);

  // Override ICashflow implementation
  Currency<double> Evaluate(
      const IPricingEnvironment<double>& environment,
      const std::string& valuation_currency) const override {
    return EvaluateImpl(environment, valuation_currency);
  }

  // Override ICashflow implementation
  Currency<aad::a_double> Evaluate(
      const IPricingEnvironment<aad::a_double>& environment,
      const std::string& valuation_currency) const override {
    return EvaluateImpl(environment, valuation_currency);
  }

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
  std::string survival_curve_name_;
  std::unique_ptr<IDayCounter> day_counter_;
  double cds_spread_{};
};

inline CdsPremium::CdsPremium(double notional, std::string currency_code,
                              boost::gregorian::date accrual_start_date,
                              boost::gregorian::date accrual_end_date,
                              boost::gregorian::date payment_date,
                              std::string discount_curve_name,
                              std::string survival_curve_name,
                              const IDayCounter& day_counter, double cds_spread)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      accrual_start_date_(accrual_start_date),
      accrual_end_date_(accrual_end_date),
      accrual_factor_(day_counter.CalculateYearFraction(accrual_start_date,
                                                        accrual_end_date)),
      payment_date_(payment_date),
      discount_curve_name_(std::move(discount_curve_name)),
      survival_curve_name_(std::move(survival_curve_name)),
      day_counter_(day_counter.Clone()),
      cds_spread_(cds_spread) {}

inline std::string CdsPremium::GetCurrencyCode() const {
  return currency_code_;
}

template <typename T>
T CdsPremium::GetPaymentAmountImpl(
    const IPricingEnvironment<T>& environment) const {
  return T(notional_ * cds_spread_ * accrual_factor_);
}
template <typename T>
Currency<T> CdsPremium::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  const auto discount_factor =
      environment.GetDiscountFactor(discount_curve_name_, payment_date_);

  const auto survival_probability_start = environment.GetSurvivalProbability(
      survival_curve_name_, accrual_start_date_);

  const auto survival_probability_end = environment.GetSurvivalProbability(
      survival_curve_name_, accrual_end_date_);

  const auto npv = GetPaymentAmount(environment) * discount_factor * 0.5 *
                   (survival_probability_end + survival_probability_start) *
                   environment.GetFxToday(currency_code_, valuation_currency);

  return Currency(valuation_currency, T(npv));
}
}  // namespace qff_a