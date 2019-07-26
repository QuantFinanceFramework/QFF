#pragma once
#include <string>
#include "Currency.h"
#include "IMarketData.h"

namespace qff {
using std::string;

class IProduct {
 public:
  IProduct() = default;
  virtual ~IProduct() = default;

  virtual Currency evaluate(const IMarketData& market_data,
                            const string& currency_code) const = 0;
};
}  // namespace qff
