#pragma once
#include "ISwapLeg.h"
class FixedLeg :
	public ISwapLeg
{
public:
	FixedLeg() = default;
	~FixedLeg() = default;
	double evaluate(MarketData marketData, const ICurrency& currency) const override;
};

