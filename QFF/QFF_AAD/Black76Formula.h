#pragma once
#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <stdexcept>
#include <string_view>

#include "../AAD/aad_all.h"

namespace qff_a {
template <typename T>
auto Black76Formula(T forward_price, double strike, T discount_factor,
                 double time_to_maturity, T volatility,
                 std::string_view option_type) {
  const auto d1 = (log(forward_price / strike) +
                   0.5 * (volatility * volatility) * time_to_maturity) /
                  (volatility * sqrt(time_to_maturity));
  const auto d2 = d1 - (volatility * sqrt(time_to_maturity));

  if (option_type == "call") {
    return T(discount_factor * (aad::normal_cdf(d1) * forward_price -
                                aad::normal_cdf(d2) * strike));
  }
  if (option_type == "put") {
    return T(discount_factor * (aad::normal_cdf(-d2) * strike -
                                aad::normal_cdf(-d1) * forward_price));
  }
  throw std::invalid_argument("invalid option type");
}
}  // namespace qff_a