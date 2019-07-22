#include "FloatingRateCoupon.h"

namespace qff {
FloatingRateCoupon::FloatingRateCoupon(double notional, date paymentDate,
                                       date accrualStartDate,
                                       date accrualEndDate,
                                       const IDayCounter& dayCounter,
                                       const IIndex& index, double leverage,
                                       double margin) {}

double FloatingRateCoupon::getPaymentAmount(
    const IMarketData& marketData) const {
  return notional_ * getRate(marketData) * calculateAccrualFactor();
}

double FloatingRateCoupon::getRate(const IMarketData& marketData) const {
  return leverage_ + margin_;
}
}  // namespace qff
