#pragma once
#include "MarketData.h"
#include "ICurrency.h"

class ICashFlow
{
public:
	ICashFlow() = default;
	virtual ~ICashFlow() = default;

	virtual double evaluate(const MarketData& marketData, const ICurrency& currency) const = 0;
};

