#pragma once
#include "IProduct.h"
#include <memory>

namespace qff {
class Swap : public IProduct {
 public:
  Swap() = default;
  Swap(std::unique_ptr<IProduct> receive_leg,
       std::unique_ptr<IProduct> pay_leg);

  Currency Evaluate(const IMarketData& market_data,
                    const std::string& currency_code) const override;

 private:
  std::unique_ptr<IProduct> receive_leg_;
  std::unique_ptr<IProduct> pay_leg_;
};
}  // namespace qff
