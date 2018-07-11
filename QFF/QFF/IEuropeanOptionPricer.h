#pragma once
#include "IMarketData.h"
#include "BasicTradeInfo.h"
#include "ICurrency.h"

class IEuropeanOptionPricer
{
public:
	IEuropeanOptionPricer() = default;
	virtual ~IEuropeanOptionPricer() = default;
	virtual double evaluate(const IMarketData& marketData, const BasicTradeInfo& basicTradeInfo, string optionType, const ICurrency& currency) const = 0;
};
