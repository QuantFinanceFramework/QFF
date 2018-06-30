#pragma once
#include "MarketData.h"
#include "ICurrency.h"

class ISwapLeg
{
public:
	ISwapLeg() = default;
	virtual ~ISwapLeg() = default;
	virtual double evaluate(MarketData marketData, const ICurrency& currency) const = 0;

};

