#pragma once
#include "Coupon.h"
#include "IMarketData.h"
#include "IIndex.h"
#include <memory>

namespace qff {
	using std::unique_ptr;

class FloatingRateCoupon : public Coupon {
 public:
  FloatingRateCoupon() = default;
  FloatingRateCoupon(double notional, date paymentDate, date accrualStartDate,
                     date accrualEndDate, const IDayCounter& dayCounter,
                     const IIndex& index, double leverage, double margin);

  ~FloatingRateCoupon() = default;

  double getPaymentAmount(const IMarketData& marketData) const override;

 private:
  double getRate(const IMarketData& marketData) const;

  unique_ptr<IIndex> index_;
  double leverage_;
  double margin_;
};
}  // namespace qff