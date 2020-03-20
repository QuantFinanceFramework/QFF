#pragma once
#include <memory>

#include "IProduct.h"

namespace qff_a {
// GenericSwap can represent and evaluate any swap structures, e.g. interest
// rate swap, basis swap, cross-currency swap, credit default swap, custom swap,
// etc.. However, some specific functions, e.g. GetParRate,
// GetBasisPointValue, etc., are not available under GenericSwap.
class GenericSwap final : public IProduct {
 public:
  GenericSwap() = default;
  GenericSwap(std::unique_ptr<IProduct> receive_leg,
              std::unique_ptr<IProduct> pay_leg);

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

  std::unique_ptr<IProduct> receive_leg_;
  std::unique_ptr<IProduct> pay_leg_;
};

inline GenericSwap::GenericSwap(std::unique_ptr<IProduct> receive_leg,
                                std::unique_ptr<IProduct> pay_leg)
    : receive_leg_(std::move(receive_leg)), pay_leg_(std::move(pay_leg)) {}

template <typename T>
Currency<T> GenericSwap::EvaluateImpl(
    const IPricingEnvironment<T>& environment,
    const std::string& valuation_currency) const {
  return receive_leg_->Evaluate(environment, valuation_currency) -
         pay_leg_->Evaluate(environment, valuation_currency);
}
}  // namespace qff_a
