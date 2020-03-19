#pragma once
#include <memory>
#include <numeric>
#include <vector>

#include "ICashflow.h"
#include "IProduct.h"

namespace qff_a {

class Leg final : public IProduct {
 public:
  Leg() = default;
  explicit Leg(std::vector<std::unique_ptr<ICashflow>> cashflows);

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

  std::vector<std::unique_ptr<ICashflow>> cashflows_;
};

inline Leg::Leg(std::vector<std::unique_ptr<ICashflow>> cashflows)
    : cashflows_(std::move(cashflows)) {}

template <typename T>
Currency<T> Leg::EvaluateImpl(const IPricingEnvironment<T>& environment,
                              const std::string& valuation_currency) const {
  auto npv = std::accumulate(
      cashflows_.begin(), cashflows_.end(), T(0.0), [&](auto result, auto& p) {
        return result + p->Evaluate(environment, valuation_currency).amount;
      });
  return Currency(valuation_currency, T(npv));
}
}  // namespace qff_a