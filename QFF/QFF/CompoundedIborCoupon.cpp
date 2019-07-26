#include "CompoundedIborCoupon.h"
namespace qff {

CompoundedIborCoupon::CompoundedIborCoupon(double notional, date paymentDate,
                                           date accrualStartDate,
                                           date accrualEndDate,
                                           const IDayCounter& dayCounter,
                                           const IIndex& index, double leverage,
                                           double margin) {}

double CompoundedIborCoupon::getPaymentAmount(
    const IMarketData& marketData) const {
  return 0;
}

double CompoundedIborCoupon::getRate(const IMarketData& marketData) const {
  return 0;
}
}  // namespace qff
