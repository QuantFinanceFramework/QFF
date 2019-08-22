#pragma once
#include <string_view>

namespace qff {
double Black76Formula(double forward_price, double strike,
                      double discount_factor, double time_to_maturity,
                      double volatility, std::string_view option_type);
}  // namespace qff