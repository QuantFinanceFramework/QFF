#include "FloatingCoupon.h"

namespace qff {
FloatingCoupon::FloatingCoupon(double notional, string currency_code,
                               date accrual_start_date, date accrual_end_date,
                               date payment_date, string discount_curve_name,
                               const IDayCounter& day_counter,
                               const IIndex& index, double leverage,
                               double margin)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      accrual_start_date_(accrual_start_date),
      accrual_end_date_(accrual_end_date),
      accrual_factor_(day_counter.CalculateYearFraction(accrual_start_date,
                                                        accrual_end_date)),
      payment_date_(payment_date),
      discount_curve_name_(std::move(discount_curve_name)),
      day_counter_(day_counter.Clone()),
      index_(index.Clone()),
      leverage_(leverage),
      margin_(margin) {}

Currency FloatingCoupon::Evaluate(const IMarketData& market_data,
                                  const string& currency_code) const {
  const auto discount_factor =
      market_data.GetDiscountFactor(discount_curve_name_, payment_date_);
  const auto npv = GetPaymentAmount(market_data) * discount_factor;
  return Currency(currency_code, npv);
}

date FloatingCoupon::GetPaymentDate() const { return payment_date_; }

double FloatingCoupon::GetPaymentAmount(const IMarketData& market_data) const {
  return notional_ * GetRate(market_data) * accrual_factor_;
}

double FloatingCoupon::GetRate(const IMarketData& market_data) const {
  return leverage_ * index_->GetRate(accrual_start_date_, accrual_end_date_,
                                     market_data) +
         margin_;
}
}  // namespace qff