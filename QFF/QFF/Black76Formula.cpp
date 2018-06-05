#include "Black76Formula.h"
#include <cmath>
#include <boost\math\distributions\normal.hpp>
using boost::math::normal;
using boost::math::cdf;

double Black76Formula(double forwardPrice, double strike, double rate, double timeToMaturity, double volatility, double dividend, string optionType)
{
	double d1 = (log(forwardPrice / strike) + 0.5*(volatility*volatility)*timeToMaturity)/(volatility*sqrt(timeToMaturity));
	double d2 = d1 - (volatility * sqrt(timeToMaturity));

	if (optionType == "call")
	{
		return exp(-rate * timeToMaturity)*(cdf(normal(), d1)*forwardPrice - cdf(normal(), d2)*strike);
	}
	else if (optionType == "put")
	{
		return exp(-rate * timeToMaturity)*(cdf(normal(), -d2)*strike - cdf(normal(), -d1)*forwardPrice);
	}
	else
	{
		//throw error?
		return 0;
	}

}
