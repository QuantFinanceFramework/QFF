#include "FixedCoupon.h"

namespace qff {
FixedCoupon::FixedCoupon(double notional, date paymentDate,
                                 date accrualStartDate, date accrualEndDate,
                                 const IDayCounter& day_counter, double rate) {}

double FixedCoupon::GetPaymentAmount(const IMarketData& market_data) const {
  return notional_ * rate_ * accrual_factor_;
}
}  // namespace qff
