#include "Swap.h"

namespace qff {
using std::move;

Swap::Swap(Leg&& receiveLeg, Leg&& payLeg)
    : receiveLeg_(move(receiveLeg)), payLeg_(move(payLeg)) {}

Currency Swap::evaluate(const IMarketData& marketData,
                        const string& currencyCode) const {
  return Currency();
}
}  // namespace qff