#pragma once
#include <memory>

#include "FixedLeg.h"
#include "FloatingLeg.h"
#include "IProduct.h"

namespace qff_a {
class InterestRateSwap final : public IProduct {
 public:
  InterestRateSwap() = default;
  InterestRateSwap(std::unique_ptr<FixedLeg> fixed_leg,
                   std::unique_ptr<FloatingLeg> floating_leg);

  template <typename T>
  T GetBasisPointValue(const IPricingEnvironment<T>& environment) const;

  template <typename T>
  T GetParRate(const IPricingEnvironment<T>& environment) const;

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

  std::unique_ptr<FixedLeg> fixed_leg_;
  std::unique_ptr<FloatingLeg> floating_leg_;
};

inline InterestRateSwap::InterestRateSwap(
    std::unique_ptr<FixedLeg> fixed_leg,
    std::unique_ptr<FloatingLeg> floating_leg)
    : fixed_leg_(std::move(fixed_leg)),
      floating_leg_(std::move(floating_leg)) {}

template <typename T>
T InterestRateSwap::GetBasisPointValue(
    const IPricingEnvironment<T>& environment) const {
  return fixed_leg_->GetBasisPointValue(environment);
}

template <typename T>
T InterestRateSwap::GetParRate(
    const IPricingEnvironment<T>& environment) const {
  return T(floating_leg_->Evaluate(environment).amount /
           GetBasisPointValue(environment) * 0.0001);
}

template <typename T>
Currency<T> InterestRateSwap::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  return fixed_leg_->Evaluate(environment, valuation_currency) -
         floating_leg_->Evaluate(environment, valuation_currency);
}
}  // namespace qff_a
