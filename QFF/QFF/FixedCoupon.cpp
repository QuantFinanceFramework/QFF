#include "FixedCoupon.h"

namespace qff {
FixedCoupon::FixedCoupon(double notional, date paymentDate,
                                 date accrualStartDate, date accrualEndDate,
                                 const IDayCounter& dayCounter, double rate) {}

double FixedCoupon::getPaymentAmount(const IMarketData& marketData) const {
  return notional_ * rate_ * accrualFactor_;
}
}  // namespace qff
