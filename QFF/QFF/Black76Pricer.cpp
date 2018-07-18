#include "Black76Pricer.h"
#include "Black76Formula.h"

double Black76Pricer::evaluate(const IMarketData& marketData, const BasicTradeInfo& basicTradeInfo, string optionType, const ICurrency & currency) const
{	
	//TODO: Make Black76Formula takes discount factor instead of zero rate and time to maturity. 
	//return Black76Formula(marketData.getForward(basicTradeInfo.underlying,basicTradeInfo.expiryDate), 
	//	basicTradeInfo.strike, 
	//	marketData.getZeroRate("AUD_STD", basicTradeInfo.expiryDate),
	//	basicTradeInfo.timeToMaturity, 
	//	marketData.getVolatility(basicTradeInfo.underlying, basicTradeInfo.expiryDate, basicTradeInfo.strike),
	//	optionType);
	return 0;

}
