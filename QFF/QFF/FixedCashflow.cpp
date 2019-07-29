#include "FixedCashflow.h"
namespace qff {
FixedCashflow::FixedCashflow(double payment_amount, string currency_code,
                             date payment_date, string discount_curve_name)
    : payment_amount_(payment_amount),
      currency_code_(std::move(currency_code)),
      payment_date_(payment_date),
      discount_curve_name_(std::move(discount_curve_name)) {}

date FixedCashflow::GetPaymentDate() const { return payment_date_; }

double FixedCashflow::GetPaymentAmount(const IMarketData& market_data) const {
  return payment_amount_;
}
}  // namespace qff
