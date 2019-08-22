#include "Swap.h"

using std::string;

namespace qff {

Swap::Swap(std::unique_ptr<IProduct> receive_leg,
           std::unique_ptr<IProduct> pay_leg)
    : receive_leg_(move(receive_leg)), pay_leg_(std::move(pay_leg)) {}

Currency Swap::Evaluate(const IMarketData& market_data,
                        const string& currency_code) const {
  return receive_leg_->Evaluate(market_data, currency_code) -
         pay_leg_->Evaluate(market_data, currency_code);
}
}  // namespace qff