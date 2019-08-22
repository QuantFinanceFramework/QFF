#include "CdsProtection.h"

using boost::gregorian::date;
using std::string;

namespace qff {
CdsProtection::CdsProtection(double notional, string currency_code,
                             date start_date, date end_date,
                             string discount_curve_name,
                             string survival_curve_name, double recovery_rate)
    : notional_(notional),
      currency_code_(std::move(currency_code)),
      start_date_(start_date),
      end_date_(end_date),
      discount_curve_name_(std::move(discount_curve_name)),
      survival_curve_name_(std::move(survival_curve_name)),
      recovery_rate_(recovery_rate) {}

Currency CdsProtection::Evaluate(const IMarketData& market_data,
                                 const string& currency_code) const {
  return Currency();
}
}  // namespace qff
