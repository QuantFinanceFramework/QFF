#include "Leg.h"
#include <numeric>

namespace qff {

Leg::Leg(vector<unique_ptr<ICashflow>> cashflows)
    : cashflows_(std::move(cashflows)) {}

Currency Leg::Evaluate(const IMarketData& market_data,
                       const string& currency_code) const {
  const auto npv = std::accumulate(
      cashflows_.begin(), cashflows_.end(), Currency(currency_code, 0.0), [&](auto result, auto& p) {
        return result + p->Evaluate(market_data, currency_code);
      });
    return npv;
}
}  // namespace qff