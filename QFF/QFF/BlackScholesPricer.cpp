#include "BlackScholesPricer.h"
#include "BlackScholesFormula.h"

double BlackScholesPricer::evaluate(const IMarketData& marketData, const EuroOptionInfo& euroOptionInfo, string optionType, const ICurrency& currency) const
{ 	

	return BlackScholesFormula(
		marketData.getSpot(euroOptionInfo.underlying),
		euroOptionInfo.strike,
		marketData.getDiscountFactor("AUD_STD", euroOptionInfo.expiryDate),
		euroOptionInfo.timeToMaturity,
		marketData.getVolatility(euroOptionInfo.underlying, euroOptionInfo.expiryDate, euroOptionInfo.strike),
		optionType);

}
