#include "IborCoupon.h"

namespace qff {
IborCoupon::IborCoupon(double notional, date paymentDate,
                                       date accrualStartDate,
                                       date accrualEndDate,
                                       const IDayCounter& day_counter,
                                       const IIndex& index, double leverage,
                                       double margin) {}

double IborCoupon::GetPaymentAmount(
    const IMarketData& market_data) const {
  return notional_ * GetRate(market_data) * accrual_factor_;
}

double IborCoupon::GetRate(const IMarketData& market_data) const {
  return leverage_ * index_->GetRate(accrual_start_date_, market_data) + margin_;
}
}  // namespace qff
