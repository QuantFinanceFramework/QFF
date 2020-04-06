#pragma once
#include <numeric>
#include <vector>

#include "BaseCalendar.h"
#include "IProduct.h"
#include "SwapMaker.h"

namespace qff_a {
class ProtectionLeg final : public IProduct {
 public:
  ProtectionLeg(double notional, std::string currency_code,
                boost::gregorian::date start_date,
                boost::gregorian::date end_date,
                std::string discount_curve_name,
                std::string survival_curve_name, double recovery_rate,
                Frequency estimation_frequency);

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
  boost::gregorian::date start_date_;
  boost::gregorian::date end_date_;
  std::string discount_curve_name_;
  std::string survival_curve_name_;
  double recovery_rate_{};
  Frequency estimation_frequency_;
  mutable std::vector<boost::gregorian::date> estimation_schedule_;
};

inline ProtectionLeg::ProtectionLeg(double notional, std::string currency_code,
                                    boost::gregorian::date start_date,
                                    boost::gregorian::date end_date,
                                    std::string discount_curve_name,
                                    std::string survival_curve_name,
                                    double recovery_rate,
                                    Frequency estimation_frequency)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      start_date_(start_date),
      end_date_(end_date),
      discount_curve_name_(std::move(discount_curve_name)),
      survival_curve_name_(std::move(survival_curve_name)),
      recovery_rate_(recovery_rate),
      estimation_frequency_(estimation_frequency) {}

template <typename T>
Currency<T> ProtectionLeg::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  if (estimation_schedule_.empty()) {
    estimation_schedule_ = SwapMaker::MakeUnadjustedSchedule(
        start_date_, end_date_, estimation_frequency_, BaseCalendar(), true,
        start_date_);
  }
  const auto discounted_default_probability = std::transform_reduce(
      estimation_schedule_.begin(), std::prev(estimation_schedule_.end()),
      std::next(estimation_schedule_.begin()), T(0.0), std::plus(),
      [&](auto start, auto end) {
        return (environment.GetSurvivalProbability(survival_curve_name_,
                                                   start) -
                environment.GetSurvivalProbability(survival_curve_name_, end)) *
               environment.GetDiscountFactor(discount_curve_name_, end);
      });
  const auto loss_given_default = notional_ * (1.0 - recovery_rate_);

  auto npv = loss_given_default * discounted_default_probability *
             environment.GetFxToday(currency_code_, valuation_currency);

  return Currency(valuation_currency, T(npv));
}
}  // namespace qff_a