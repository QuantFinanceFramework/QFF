#pragma once
#include "MarketData.h"
#include "BasicTradeInfo.h"
#include "ICurrency.h"

class IEuropeanOptionPricer
{
public:
	IEuropeanOptionPricer() = default;
	virtual ~IEuropeanOptionPricer() = default;
	virtual double evaluate(MarketData marketData, BasicTradeInfo basicTradeInfo, const ICurrency& currency) const = 0;
};
