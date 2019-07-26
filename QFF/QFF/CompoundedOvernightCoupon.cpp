#include "CompoundedOvernightCoupon.h"
namespace qff {

CompoundedOvernightCoupon::CompoundedOvernightCoupon(
    double notional, date payment_date, date accrual_start_date,
    date accrual_end_date, const IDayCounter& day_counter, const IIndex& index,
    Period rate_cut_off, double leverage, double margin) {}

double CompoundedOvernightCoupon::GetPaymentAmount(
    const IMarketData& market_data) const {
  return 0;
}

double CompoundedOvernightCoupon::GetRate(const IMarketData& market_data) {
  return 0;
}
}  // namespace qff
