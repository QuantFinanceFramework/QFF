#pragma once
#include "MarketData.h"
#include "ICurrency.h"

class IAsianOptionPricer
{
public:
	IAsianOptionPricer() = default;
	virtual ~IAsianOptionPricer() = default;
	virtual double evaluate(MarketData marketData, const ICurrency& currency) const = 0;
};
