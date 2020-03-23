#pragma once
#include <memory>
#include <numeric>
#include <vector>

#include "FixedCoupon.h"
#include "IProduct.h"

namespace qff_a {

class FixedLeg final : public IProduct {
 public:
  FixedLeg() = default;
  FixedLeg(std::string currency_code,
           std::vector<std::unique_ptr<FixedCoupon>> cashflows);

  std::string GetCurrencyCode() const { return currency_code_; }

  template <typename T>
  T GetBasisPointValue(const IPricingEnvironment<T>& environment) const;

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

  std::string currency_code_;
  std::vector<std::unique_ptr<FixedCoupon>> cashflows_;
};

inline FixedLeg::FixedLeg(std::string currency_code,
                          std::vector<std::unique_ptr<FixedCoupon>> cashflows)
    : currency_code_(std::move(currency_code)),
      cashflows_(std::move(cashflows)) {}

template <typename T>
T FixedLeg::GetBasisPointValue(
    const IPricingEnvironment<T>& environment) const {
  auto bpv =
      0.0001 * std::accumulate(
                   cashflows_.begin(), cashflows_.end(), T(0.0),
                   [&](auto result, auto& p) {
                     return result + p->GetScaledBasisPointValue(environment);
                   });
  return T(bpv);
}

template <typename T>
Currency<T> FixedLeg::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  auto npv = std::accumulate(
      cashflows_.begin(), cashflows_.end(), T(0.0), [&](auto result, auto& p) {
        return result + p->Evaluate(environment, valuation_currency).amount;
      });
  return Currency(valuation_currency, T(npv));
}
}  // namespace qff_a