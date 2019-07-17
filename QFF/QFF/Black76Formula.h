#pragma once
#include <string>

namespace qff {
	using std::string;

	double Black76Formula(double forwardPrice, double strike, double discountFactor, double timeToMaturity, double volatility, string optionType);
}