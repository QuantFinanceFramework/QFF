#include "AveragedOvernightCoupon.h"
#include <numeric>

namespace qff {
AveragedOvernightCoupon::AveragedOvernightCoupon(
    double notional, string currency_code, vector<date> accrual_period_dates,
    date payment_date, string discount_curve_name,
    const IDayCounter& day_counter, const IIndex& index, double leverage,
    double margin)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      accrual_period_dates_(std::move(accrual_period_dates)),
      accrual_factors_(size(accrual_period_dates_) - 1),
      payment_date_(payment_date),
      discount_curve_name_(std::move(discount_curve_name)),
      day_counter_(day_counter.Clone()),
      index_(index.Clone()),
      leverage_(leverage),
      margin_(margin) {
  std::transform(accrual_period_dates_.begin(),
                 std::prev(accrual_period_dates_.end()),
                 std::next(accrual_period_dates_.begin()),
                 accrual_factors_.begin(), [&](auto start, auto end) {
                   return day_counter_->CalculateYearFraction(start, end);
                 });
}


date AveragedOvernightCoupon::GetPaymentDate() const { return payment_date_; }

double AveragedOvernightCoupon::GetPaymentAmount(
    const IMarketData& market_data) const {
  return notional_ * GetRate(market_data) *
         day_counter_->CalculateYearFraction(*accrual_period_dates_.begin(),
                                             accrual_period_dates_.back());
}

double AveragedOvernightCoupon::GetRate(
    const IMarketData& market_data) const {
  const auto averaged_daily_rate = std::transform_reduce(
      accrual_period_dates_.begin(), std::prev(accrual_period_dates_.end()),
      accrual_factors_.begin(), 0.0, std::plus(), [&](auto start, auto factor) {
        return factor * index_->GetRate(start, market_data);
      }) / day_counter_->CalculateYearFraction(*accrual_period_dates_.begin(),
                                          accrual_period_dates_.back());

  return leverage_ * averaged_daily_rate + margin_;
}
}  // namespace qff
