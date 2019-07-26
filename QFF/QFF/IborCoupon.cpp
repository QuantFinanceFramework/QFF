#include "IborCoupon.h"

namespace qff {
IborCoupon::IborCoupon(double notional, date paymentDate,
                                       date accrualStartDate,
                                       date accrualEndDate,
                                       const IDayCounter& dayCounter,
                                       const IIndex& index, double leverage,
                                       double margin) {}

double IborCoupon::getPaymentAmount(
    const IMarketData& marketData) const {
  return notional_ * getRate(marketData) * accrualFactor_;
}

double IborCoupon::getRate(const IMarketData& marketData) const {
  return leverage_ * index_->getRate(accrualStartDate_, marketData) + margin_;
}
}  // namespace qff
