#pragma once
#include <string>

namespace qff {
using std::string;

double BlackScholesFormula(double spot, double strike, double discount_factor,
                           double time_to_maturity, double volatility,
                           const string& option_type);
}  // namespace qff