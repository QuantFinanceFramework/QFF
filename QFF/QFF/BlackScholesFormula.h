#pragma once
#include <string_view>

namespace qff {
double BlackScholesFormula(double spot, double strike, double discount_factor,
                           double time_to_maturity, double volatility,
                           std::string_view option_type);
}  // namespace qff