#include "BlackScholesPricer.h"
#include "BlackScholesFormula.h"

double BlackScholesPricer::evaluate(const MarketData& marketData, const BasicTradeInfo& basicTradeInfo, string optionType, const ICurrency& currency) const
{
	return BlackScholesFormula(marketData.price,basicTradeInfo.strike,marketData.rate,basicTradeInfo.timeToMaturity,marketData.volatility,marketData.dividend,optionType);
}
