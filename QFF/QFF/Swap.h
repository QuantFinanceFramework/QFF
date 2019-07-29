#pragma once
#include "IProduct.h"
#include "Leg.h"

namespace qff {
class Swap : public IProduct {
 public:
  Swap() = default;
  Swap(Leg&& receive_leg, Leg&& pay_leg);
  ~Swap() = default;

  Currency Evaluate(const IMarketData& market_data,
                    const string& currency_code) const override;

 private:
  Leg receiveLeg_;
  Leg payLeg_;
};
}  // namespace qff
