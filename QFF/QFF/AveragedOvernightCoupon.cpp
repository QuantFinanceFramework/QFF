#include "AveragedOvernightCoupon.h"
namespace qff {

AveragedOvernightCoupon::AveragedOvernightCoupon(
    double notional, date payment_date, date accrual_start_date,
    date accrual_end_date, const IDayCounter& day_counter, const IIndex& index,
    Period rate_cut_off, double leverage, double margin) {}

double AveragedOvernightCoupon::GetPaymentAmount(
    const IMarketData& market_data) const {
  return 0;
}

double AveragedOvernightCoupon::GetRate(const IMarketData& market_data) {
  return 0;
}

}  // namespace qff
