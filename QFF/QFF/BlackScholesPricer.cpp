#include "BlackScholesPricer.h"
#include "BlackScholesFormula.h"

double BlackScholesPricer::evaluate(const IMarketData& marketData, const BasicTradeInfo& basicTradeInfo, string optionType, const ICurrency& currency) const
{ 	
	return BlackScholesFormula(
		marketData.getSpot(basicTradeInfo.underlying),
		basicTradeInfo.strike,
		marketData.getZeroRate("AUD_STD", basicTradeInfo.expiryDate), 
		basicTradeInfo.timeToMaturity,
		marketData.getVolatility(basicTradeInfo.underlying, basicTradeInfo.expiryDate, basicTradeInfo.strike),
		marketData.getDividendYieldEstimate(basicTradeInfo.underlying, basicTradeInfo.expiryDate),
		optionType);
}
