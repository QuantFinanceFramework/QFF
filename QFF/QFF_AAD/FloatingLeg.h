#pragma once
#include <memory>
#include <numeric>
#include <vector>

#include "FloatingCoupon.h"
#include "IProduct.h"

namespace qff_a {

class FloatingLeg final : public IProduct {
 public:
  FloatingLeg() = default;
  FloatingLeg(std::string currency_code,
              std::vector<std::unique_ptr<FloatingCoupon>> cashflows);

  std::string GetCurrencyCode() const { return currency_code_; }

  template <typename T>
  T GetBasisPointValue(const IPricingEnvironment<T>& environment) const;

  template <typename T>
  T GetZeroMarginNpv(const IPricingEnvironment<T>& environment) const;

  template <typename T>
  Currency<T> Evaluate(const IPricingEnvironment<T>& environment) const {
    return EvaluateImpl(environment, GetCurrencyCode());
  }

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
  std::vector<std::unique_ptr<FloatingCoupon>> cashflows_;
};

inline FloatingLeg::FloatingLeg(
    std::string currency_code,
    std::vector<std::unique_ptr<FloatingCoupon>> cashflows)
    : currency_code_(std::move(currency_code)),
      cashflows_(std::move(cashflows)) {}

template <typename T>
T FloatingLeg::GetBasisPointValue(
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
T FloatingLeg::GetZeroMarginNpv(
    const IPricingEnvironment<T>& environment) const {
  auto npv = std::accumulate(
      cashflows_.begin(), cashflows_.end(), T(0.0), [&](auto result, auto& p) {
        return result +
               p->GetRate(environment) * GetScaledBasisPointValue(environment);
      });
  return T(npv);
}

template <typename T>
Currency<T> FloatingLeg::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  auto npv = std::accumulate(
      cashflows_.begin(), cashflows_.end(), T(0.0), [&](auto result, auto& p) {
        return result + p->Evaluate(environment, valuation_currency).amount;
      });
  return Currency(valuation_currency, T(npv));
}
}  // namespace qff_a