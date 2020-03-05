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

  std::vector<std::unique_ptr<ICashflow>> cashflows_;
};

inline Leg::Leg(std::vector<std::unique_ptr<ICashflow>> cashflows)
    : cashflows_(std::move(cashflows)) {}

template <typename T>
T Leg::EvaluateImpl(const IPricingEnvironment<T>& environment,
                    const std::string& currency_code) const {
  return T(std::accumulate(
      cashflows_.begin(), cashflows_.end(), T(0.0), [&](auto result, auto& p) {
        return result + p->Evaluate(environment, currency_code);
      }));
}
}  // namespace qff_a