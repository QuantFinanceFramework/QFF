#include "BlackScholesPricer.h"
#include "Black76Formula.h"

double BlackScholesPricer::evaluate(MarketData marketData, BasicTradeInfo basicTradeInfo, const ICurrency& currency) const
{
	return Black76Formula(marketData.price,basicTradeInfo.strike,marketData.rate,basicTradeInfo.timeToMaturity,marketData.volatility,marketData.dividend,basicTradeInfo.optionType);
}
