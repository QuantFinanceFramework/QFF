#include "Black76Pricer.h"
#include "Black76Formula.h"

double Black76Pricer::evaluate(const IMarketData& marketData, const EuroOptionInfo& euroOptionInfo, string optionType, const ICurrency & currency) const
{	

	return Black76Formula(marketData.getForward(euroOptionInfo.underlying, euroOptionInfo.expiryDate),
		euroOptionInfo.strike,
		marketData.getDiscountFactor("AUD_STD", euroOptionInfo.expiryDate),
		euroOptionInfo.timeToMaturity,
		marketData.getVolatility(euroOptionInfo.underlying, euroOptionInfo.expiryDate, euroOptionInfo.strike),
		optionType);

}
