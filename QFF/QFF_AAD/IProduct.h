#pragma once
#include "../AAD/aad_all.h"
#include "IPricingEnvironment.h"

namespace qff_a {
class IProduct {
 public:
  virtual ~IProduct() = default;

  virtual double Evaluate(const IPricingEnvironment<double>& environment,
                          const std::string& currency_code) const = 0;

  virtual aad::a_double Evaluate(
      const IPricingEnvironment<aad::a_double>& environment,
      const std::string& currency_code) const = 0;
};
}  // namespace qff_a