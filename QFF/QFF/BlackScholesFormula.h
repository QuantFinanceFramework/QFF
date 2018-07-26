#pragma once
#include <string>
using std::string;

double BlackScholesFormula(double spot, double strike, double discountFactor, double timeToMaturity, double volatility, string optionType);
