#pragma once
#include <memory>

#include "FloatingLeg.h"
#include "IProduct.h"

namespace qff_a {
class BasisSwap final : public IProduct {
 public:
  BasisSwap() = default;
  BasisSwap(std::unique_ptr<FloatingLeg> margin_leg,
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

  std::unique_ptr<FloatingLeg> margin_leg_;
  std::unique_ptr<FloatingLeg> floating_leg_;
};

inline BasisSwap::BasisSwap(std::unique_ptr<FloatingLeg> margin_leg,
                            std::unique_ptr<FloatingLeg> floating_leg)
    : margin_leg_(std::move(margin_leg)),
      floating_leg_(std::move(floating_leg)) {}

template <typename T>
T BasisSwap::GetBasisPointValue(
    const IPricingEnvironment<T>& environment) const {
  return margin_leg_->GetBasisPointValue(environment);
}

template <typename T>
T BasisSwap::GetParRate(const IPricingEnvironment<T>& environment) const {
  return T((floating_leg_->Evaluate(environment).amount -
            margin_leg_->GetZeroMarginNpv(environment)) /
           GetBasisPointValue(environment) * 0.0001);
}

template <typename T>
Currency<T> BasisSwap::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  return margin_leg_->Evaluate(environment, valuation_currency) -
         floating_leg_->Evaluate(environment, valuation_currency);
}
}  // namespace qff_a
