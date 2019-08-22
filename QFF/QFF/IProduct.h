#pragma once
#include <string>
#include "Currency.h"
#include "IMarketData.h"

namespace qff {
class IProduct {
 public:
  IProduct() = default;
  virtual ~IProduct() = default;

  virtual Currency Evaluate(const IMarketData& market_data,
                            const std::string& currency_code) const = 0;
};
}  // namespace qff
