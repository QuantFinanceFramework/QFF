#pragma once
#include "IMarketData.h"
#include "BasicTradeInfo.h"
#include "ICurrency.h"

class IAsianOptionPricer
{
public:
	IAsianOptionPricer() = default;
	virtual ~IAsianOptionPricer() = default;
	virtual double evaluate(const IMarketData& marketData, const BasicTradeInfo& basicTradeInfo, const ICurrency& currency) const = 0;
};
