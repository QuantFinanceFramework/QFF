#include "CompoundedOvernightCoupon.h"
namespace qff {

CompoundedOvernightCoupon::CompoundedOvernightCoupon(
    double notional, date paymentDate, date accrualStartDate,
    date accrualEndDate, const IDayCounter& dayCounter, const IIndex& index,
    Period rate_cut_off, double leverage, double margin) {}

double CompoundedOvernightCoupon::getPaymentAmount(
    const IMarketData& marketData) const {
  return 0;
}

double CompoundedOvernightCoupon::getRate(const IMarketData& marketData) const {
  return 0;
}
}  // namespace qff
