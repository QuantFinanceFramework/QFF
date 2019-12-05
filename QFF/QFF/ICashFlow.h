#pragma once
#include "IMarketData.h"
#include "IProduct.h"

namespace qff {
class ICashflow : public IProduct{
 public:
  virtual ~ICashflow() = default;

  virtual boost::gregorian::date GetPaymentDate() const = 0;
  virtual double GetPaymentAmount(const IMarketData& market_data) const = 0;
};
}  // namespace qff
