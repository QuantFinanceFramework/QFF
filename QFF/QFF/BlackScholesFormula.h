#pragma once
#include <string>

namespace qff {
using std::string;

double BlackScholesFormula(double spot, double strike, double discountFactor,
                           double timeToMaturity, double volatility,
                           string optionType);
}  // namespace qff