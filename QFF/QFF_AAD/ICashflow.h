#pragma once
#include "IPricingEnvironment.h"
#include "IProduct.h"

namespace qff_a {
class ICashflow : public IProduct {
 public:
  virtual ~ICashflow() = default;

  double Evaluate(const IPricingEnvironment<double>& environment,
                  const std::string& currency_code) const override final {
    return EvaluateImpl(environment, currency_code);
  }

  aad::a_double Evaluate(
      const IPricingEnvironment<aad::a_double>& environment,
      const std::string& currency_code) const override final {
    return EvaluateImpl(environment, currency_code);
  }

  virtual boost::gregorian::date GetPaymentDate() const = 0;

  virtual std::string GetDiscountCurveName() const = 0;

  virtual double GetPaymentAmount(
      const IPricingEnvironment<double>& environment) const = 0;

  virtual aad::a_double GetPaymentAmount(
      const IPricingEnvironment<aad::a_double>& environment) const = 0;

 private:
  template <typename T>
  T EvaluateImpl(const IPricingEnvironment<T>& environment,
                 const std::string& currency_code) const;
};

template <typename T>
T ICashflow::EvaluateImpl(const IPricingEnvironment<T>& environment,
                          const std::string& currency_code) const {
  return T(
      GetPaymentAmount(environment) *
      environment.GetDiscountFactor(GetDiscountCurveName(), GetPaymentDate()));
}
}  // namespace qff_a
