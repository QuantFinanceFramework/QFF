#include "Leg.h"
#include <numeric>

namespace qff {
using std::accumulate;
using std::move;

Leg::Leg(vector<unique_ptr<ICashflow>> cashflows) {}

Currency Leg::evaluate(const IMarketData& market_data,
                       const string& currency_code) const {
  return Currency();
}
}  // namespace qff