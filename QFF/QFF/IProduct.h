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

  virtual Currency evaluate(const IMarketData& marketData,
                            const string& currencyCode) const = 0;
};
}  // namespace qff
