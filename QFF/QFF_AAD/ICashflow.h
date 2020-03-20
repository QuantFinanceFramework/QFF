#pragma once
#include "IProduct.h"

namespace qff_a {
class ICashflow : public IProduct {
 public:
  virtual ~ICashflow() = default;

  virtual std::string GetCurrencyCode() const = 0;

  virtual boost::gregorian::date GetPaymentDate() const = 0;

  virtual std::string GetDiscountCurveName() const = 0;

 protected:
  template <typename T>
  bool IsExpired(const IPricingEnvironment<T>& environment) const;
};

template <typename T>
bool ICashflow::IsExpired(const IPricingEnvironment<T>& environment) const {
  if (GetPaymentDate() < environment.GetPricingDate()) {
    return true;
  }
  return false;
}
}  // namespace qff_a
