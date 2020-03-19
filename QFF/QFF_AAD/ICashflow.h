#pragma once
#include "IProduct.h"

namespace qff_a {
class ICashflow : public IProduct {
 public:
  virtual ~ICashflow() = default;

  virtual std::string GetCurrencyCode() const = 0;

  virtual boost::gregorian::date GetPaymentDate() const = 0;

  virtual std::string GetDiscountCurveName() const = 0;
};
}  // namespace qff_a
