#include "FixedCashflow.h"

using boost::gregorian::date;
using std::string;

namespace qff {
FixedCashflow::FixedCashflow(double payment_amount, string currency_code,
                             date payment_date, string discount_curve_name)
    : payment_amount_(payment_amount),
      currency_code_(std::move(currency_code)),
      payment_date_(payment_date),
      discount_curve_name_(std::move(discount_curve_name)) {}

Currency FixedCashflow::Evaluate(const IMarketData& market_data,
                                 const string& currency_code) const {
  const auto discount_factor =
      market_data.GetDiscountFactor(discount_curve_name_, payment_date_);
  const auto npv = GetPaymentAmount(market_data) * discount_factor;
  return Currency(currency_code, npv);
}

date FixedCashflow::GetPaymentDate() const { return payment_date_; }

double FixedCashflow::GetPaymentAmount(const IMarketData& market_data) const {
  return payment_amount_;
}
}  // namespace qff
