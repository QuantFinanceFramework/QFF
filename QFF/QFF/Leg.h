#pragma once
#include <memory>
#include <vector>
#include "ICashflow.h"
#include "IProduct.h"

namespace qff {

class Leg : public IProduct {
 public:
  Leg() = default;
  Leg(std::vector<std::unique_ptr<ICashflow>> cashflows);

  Currency Evaluate(const IMarketData& market_data,
                    const std::string& currency_code) const override;

 private:
  std::vector<std::unique_ptr<ICashflow>> cashflows_;
};
}  // namespace qff