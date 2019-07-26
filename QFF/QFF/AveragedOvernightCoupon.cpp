#include "AveragedOvernightCoupon.h"
namespace qff {

AveragedOvernightCoupon::AveragedOvernightCoupon(
    double notional, date paymentDate, date accrualStartDate,
    date accrualEndDate, const IDayCounter& dayCounter, const IIndex& index,
    Period rate_cut_off, double leverage, double margin) {}

double AveragedOvernightCoupon::getPaymentAmount(
    const IMarketData& marketData) const {
  return 0;
}

double AveragedOvernightCoupon::getRate(const IMarketData& marketData) const {
  return 0;
}

}  // namespace qff
