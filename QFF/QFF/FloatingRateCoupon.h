#pragma once
#include "Coupon.h"
#include "IMarketData.h"
#include "Index.h"

namespace qff {
class FloatingRateCoupon : public Coupon {
 public:
  FloatingRateCoupon() = default;
  FloatingRateCoupon(double notional, date paymentDate, date accrualStartDate,
                     date accrualEndDate, const IDayCounter& dayCounter,
                     Index index, double leverage, double margin);

  ~FloatingRateCoupon() = default;

  double getPaymentAmount(const IMarketData& marketData) const override;

 private:
  double getRate(const IMarketData& marketData) const;

  Index index_;
  double leverage_;
  double margin_;
};
}  // namespace qff