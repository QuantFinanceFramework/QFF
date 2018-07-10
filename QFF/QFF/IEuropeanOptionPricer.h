#pragma once
#include "MarketData.h"
#include "BasicTradeInfo.h"
#include "ICurrency.h"

class IEuropeanOptionPricer
{
public:
	IEuropeanOptionPricer() = default;
	virtual ~IEuropeanOptionPricer() = default;
	virtual double evaluate(const MarketData& marketData, const BasicTradeInfo& basicTradeInfo, string optionType, const ICurrency& currency) const = 0;
};
