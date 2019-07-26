#include "CompoundedIborCoupon.h"
namespace qff {
CompoundedIborCoupon::CompoundedIborCoupon(
    double notional, string currency_code, vector<date> accrual_period_dates,
    date payment_date, const IDayCounter& day_counter, const IIndex& index,
    double leverage, double margin)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      accrual_period_dates_(std::move(accrual_period_dates)),
      payment_date_(payment_date),
      day_counter_(day_counter.Clone()),
      index_(index.Clone()),
      leverage_(leverage),
      margin_(margin) {}

double CompoundedIborCoupon::GetPaymentAmount(
    const IMarketData& market_data) const {
  return 0;
}

double CompoundedIborCoupon::GetRate(const IMarketData& market_data) {
  return 0;
}
}  // namespace qff
