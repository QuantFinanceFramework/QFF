#include "AveragedOvernightCoupon.h"
#include <utility>

namespace qff {
AveragedOvernightCoupon::AveragedOvernightCoupon(
    double notional, string currency_code, vector<date> accrual_period_dates,
    date payment_date, string discount_curve_name,
    const IDayCounter& day_counter, const IIndex& index, double leverage,
    double margin, Period rate_cut_off)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      accrual_period_dates_(std::move(accrual_period_dates)),
      payment_date_(payment_date),
      discount_curve_name_(std::move(discount_curve_name)),
      day_counter_(day_counter.Clone()),
      index_(index.Clone()),
      leverage_(leverage),
      margin_(margin),
      rate_cut_off_(rate_cut_off) {}

double AveragedOvernightCoupon::GetPaymentAmount(
    const IMarketData& market_data) const {
  return 0;
}

double AveragedOvernightCoupon::GetRate(const IMarketData& market_data) {
  return 0;
}

}  // namespace qff
