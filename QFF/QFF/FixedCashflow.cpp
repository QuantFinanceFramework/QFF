#include "FixedCashflow.h"
namespace qff {
FixedCashflow::FixedCashflow(double payment_amount, string currency_code,
                             date payment_date)
    : payment_amount_(payment_amount),
      currency_code_(std::move(currency_code)),
      payment_date_(payment_date) {}

date FixedCashflow::GetPaymentDate() const { return payment_date_; }

double FixedCashflow::GetPaymentAmount(const IMarketData& market_data) const {
  return payment_amount_;
}
}  // namespace qff
