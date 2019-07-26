#include "CompoundedIborCoupon.h"
namespace qff {

CompoundedIborCoupon::CompoundedIborCoupon(double notional, date payment_date,
                                           date accrual_start_date,
                                           date accrual_end_date,
                                           const IDayCounter& day_counter,
                                           const IIndex& index, double leverage,
                                           double margin) {}

double CompoundedIborCoupon::GetPaymentAmount(
    const IMarketData& market_data) const {
  return 0;
}

double CompoundedIborCoupon::GetRate(const IMarketData& market_data) {
  return 0;
}
}  // namespace qff
