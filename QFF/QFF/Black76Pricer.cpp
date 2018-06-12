#include "Black76Pricer.h"
#include "Black76Formula.h"

double Black76Pricer::evaluate(MarketData marketData, BasicTradeInfo basicTradeInfo, string optionType, const ICurrency& currency) const
{
	return Black76Formula(marketData.price, basicTradeInfo.strike, marketData.rate, basicTradeInfo.timeToMaturity, marketData.volatility, optionType);
}