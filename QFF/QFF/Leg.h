#pragma once
#include <memory>
#include <vector>
#include "ICashflow.h"
#include "IProduct.h"

namespace qff {
using std::unique_ptr;
using std::vector;

class Leg : public IProduct {
 public:
  Leg() = default;
  Leg(vector<unique_ptr<ICashflow>> cashflows);

  Leg(const Leg&) = delete;
  Leg& operator=(const Leg&) = delete;

  Leg(Leg&&) = default;
  Leg& operator=(Leg&&) = default;

  ~Leg() = default;

  Currency evaluate(const IMarketData& market_data,
                    const string& currency_code) const override;

 private:
  vector<unique_ptr<ICashflow>> cashflows_;
};
}  // namespace qff