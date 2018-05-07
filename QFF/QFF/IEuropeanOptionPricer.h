#pragma once
#include "MarketData.h"
#include "ICurrency.h"

class IEuropeanOptionPricer
{
public:
	IEuropeanOptionPricer() = default;
	virtual ~IEuropeanOptionPricer() = default;
	virtual double evaluate(MarketData marketData, const ICurrency& currency) const = 0;
};
