#include "FixedRateCoupon.h"

namespace qff {
FixedRateCoupon::FixedRateCoupon(double notional, date paymentDate,
                                 date accrualStartDate, date accrualEndDate,
                                 const IDayCounter& dayCounter, double rate) {}

double FixedRateCoupon::getPaymentAmount(const IMarketData& marketData) const {
  return notional_ * rate_ * calculateAccrualFactor();
}
}  // namespace qff
