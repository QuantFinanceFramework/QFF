#pragma once
#include "IMarketData.h"

namespace qff {
class ICashflow {
 public:
  ICashflow() = default;
  virtual ~ICashflow() = default;

  virtual date GetPaymentDate() const = 0;
  virtual double GetPaymentAmount(const IMarketData& market_data) const = 0;
};
}  // namespace qff
