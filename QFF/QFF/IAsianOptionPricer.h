#pragma once
#include "MarketData.h"
#include "BasicTradeInfo.h"
#include "ICurrency.h"

class IAsianOptionPricer
{
public:
	IAsianOptionPricer() = default;
	virtual ~IAsianOptionPricer() = default;
	virtual double evaluate(MarketData marketData, BasicTradeInfo basicTradeInfo, const ICurrency& currency) const = 0;
};
