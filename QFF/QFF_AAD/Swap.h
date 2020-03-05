#pragma once
#include <memory>

#include "IProduct.h"

namespace qff_a {
class Swap final : public IProduct {
 public:
  Swap() = default;
  Swap(std::unique_ptr<IProduct> receive_leg,
       std::unique_ptr<IProduct> pay_leg);

  double Evaluate(const IPricingEnvironment<double>& environment,
                  const std::string& currency_code) const override {
    return EvaluateImpl(environment, currency_code);
  }

  aad::a_double Evaluate(const IPricingEnvironment<aad::a_double>& environment,
                         const std::string& currency_code) const override {
    return EvaluateImpl(environment, currency_code);
  }

 private:
  template <typename T>
  T EvaluateImpl(const IPricingEnvironment<T>& environment,
                 const std::string& currency_code) const;

  std::unique_ptr<IProduct> receive_leg_;
  std::unique_ptr<IProduct> pay_leg_;
};

inline Swap::Swap(std::unique_ptr<IProduct> receive_leg,
                  std::unique_ptr<IProduct> pay_leg)
    : receive_leg_(std::move(receive_leg)), pay_leg_(std::move(pay_leg)) {}

template <typename T>
T Swap::EvaluateImpl(const IPricingEnvironment<T>& environment,
                     const std::string& currency_code) const {
  return T(receive_leg_->Evaluate(environment, currency_code) -
           pay_leg_->Evaluate(environment, currency_code));
}
}  // namespace qff_a
