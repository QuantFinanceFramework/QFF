#pragma once
#include "IPricingEnvironment.h"
#include "IProduct.h"

namespace qff_a {
class ICashflow : public IProduct {
 public:
  virtual ~ICashflow() = default;

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

  virtual std::string GetCurrencyCode() const = 0;

  virtual boost::gregorian::date GetPaymentDate() const = 0;

  virtual std::string GetDiscountCurveName() const = 0;

  virtual double GetPaymentAmount(
      const IPricingEnvironment<double>& environment) const = 0;

  virtual aad::a_double GetPaymentAmount(
      const IPricingEnvironment<aad::a_double>& environment) const = 0;

 private:
  template <typename T>
  Currency<T> EvaluateImpl(const IPricingEnvironment<T>& environment,
                           const std::string& valuation_currency) const;
};

template <typename T>
Currency<T> ICashflow::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  auto npv =
      GetPaymentAmount(environment) *
      environment.GetDiscountFactor(GetDiscountCurveName(), GetPaymentDate()) *
      environment.GetFxToday(GetCurrencyCode(), valuation_currency);

  return Currency(valuation_currency, T(npv));
}
}  // namespace qff_a
