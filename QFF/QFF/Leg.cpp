#include "Leg.h"
#include <numeric>

namespace qff {

Leg::Leg(vector<unique_ptr<ICashflow>> cashflows)
    : cashflows_(std::move(cashflows)) {}

Currency Leg::evaluate(const IMarketData& market_data,
                       const string& currency_code) const {
  const auto amount = std::accumulate(
      cashflows_.begin(), cashflows_.end(), 0.0, [&](double result, auto& p) {
        return result + p->GetPaymentAmount(market_data);
      });
    return Currency(currency_code, amount);
}
}  // namespace qff