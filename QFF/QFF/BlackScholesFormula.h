#pragma once
#include <string>
using std::string;

double BlackScholesFormula(double spot, double strike, double rate, double timeToMaturity, double volatility, string optionType);
