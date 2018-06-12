#include "BlackScholesFormula.h"
#include <cmath>
#include <boost\math\distributions\normal.hpp>
#include <stdexcept>

using boost::math::normal;
using boost::math::cdf;

double BlackScholesFormula(double spot, double strike, double rate, double timeToMaturity, double volatility, double dividend, string optionType)
{
	double d1 = (log(spot / strike) + ((rate - dividend) + 0.5*volatility*volatility)*timeToMaturity) / (volatility*sqrt(timeToMaturity));
	double d2 = d1 - (volatility * sqrt(timeToMaturity));

	if (optionType == "call")
	{
		return exp(-dividend * timeToMaturity)*spot*cdf(normal(), d1) - exp(-rate * timeToMaturity)*strike*cdf(normal(), d2);
	}
	else if (optionType == "put")
	{
		return exp(-rate * timeToMaturity)*strike*cdf(normal(), -d2) - exp(-dividend * timeToMaturity)*spot*cdf(normal(), -d1);
	}
	else
	{
		//throw error?
		//throw std::invalid_argument("invalid option type");
		return 0;
	}

}