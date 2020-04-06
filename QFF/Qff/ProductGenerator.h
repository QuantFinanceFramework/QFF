#pragma once
#include <memory>

#include "IProduct.h"

namespace qff_a {
class ProductGenerator {
 public:
  // Make product using pre-defined generator. Generator names follow Bloomberg
  // tickers, e.g. "USSO", "USOSFR", "USSWAP", etc..
  static std::unique_ptr<IProduct> MakeProduct(
      std::string_view generator_name, double notional,
      boost::gregorian::date start_date, boost::gregorian::date maturity_date,
      double market_quote);
};
}  // namespace qff_a
