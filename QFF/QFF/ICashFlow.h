#pragma once
#include "IMarketData.h"

namespace qff {
class ICashflow {
 public:
  ICashflow() = default;
  virtual ~ICashflow() = default;

  virtual date getPaymentDate() const = 0;
  virtual double getPaymentAmount(const IMarketData& marketData) const = 0;
};
}  // namespace qff
