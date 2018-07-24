#include "Black76Pricer.h"
#include "Black76Formula.h"

double Black76Pricer::evaluate(const IMarketData& marketData, const BasicTradeInfo& basicTradeInfo, string optionType, const ICurrency & currency) const
{	

	return Black76Formula(marketData.getForward(basicTradeInfo.underlying,basicTradeInfo.expiryDate), 
		basicTradeInfo.strike, 
		marketData.getDiscountFactor("AUD_STD", basicTradeInfo.expiryDate),
		basicTradeInfo.timeToMaturity, 
		marketData.getVolatility(basicTradeInfo.underlying, basicTradeInfo.expiryDate, basicTradeInfo.strike),
		optionType);

}
