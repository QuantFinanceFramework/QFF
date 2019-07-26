#pragma once
#include <memory>
#include "ICashflow.h"
#include "IDayCounter.h"

namespace qff {
class FixedCoupon : public ICashflow {
 public:
  FixedCoupon() = default;
  FixedCoupon(double notional, date accrualStartDate, date accrualEndDate,
              date paymentDate, const IDayCounter& dayCounter, double rate);

  ~FixedCoupon() = default;

  double getPaymentAmount(const IMarketData& marketData) const override;

 private:
  double notional_;
  string currencyCode_;
  date accrualStartDate_;
  date accrualEndDate_;
  double accrualFactor_;
  date paymentDate_;
  unique_ptr<IDayCounter> dayCounter_;
  double rate_;
};
}  // namespace qff