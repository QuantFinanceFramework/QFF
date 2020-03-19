#pragma once
#include "../AAD/aad_all.h"
#include "Currency.h"
#include "IPricingEnvironment.h"

namespace qff_a {
class IProduct {
 public:
  virtual ~IProduct() = default;

  virtual Currency<double> Evaluate(
      const IPricingEnvironment<double>& environment,
      const std::string& valuation_currency) const = 0;

  virtual Currency<aad::a_double> Evaluate(
      const IPricingEnvironment<aad::a_double>& environment,
      const std::string& valuation_currency) const = 0;
};
}  // namespace qff_a