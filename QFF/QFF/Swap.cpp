#include "Swap.h"

namespace qff {
using std::move;

Swap::Swap(Leg&& receive_leg, Leg&& pay_leg)
    : receiveLeg_(move(receive_leg)), payLeg_(move(pay_leg)) {}

Currency Swap::evaluate(const IMarketData& market_data,
                        const string& currency_code) const {
  return Currency();
}
}  // namespace qff