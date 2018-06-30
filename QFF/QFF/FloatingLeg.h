#pragma once
#include "ISwapLeg.h"
class FloatingLeg :
	public ISwapLeg
{
public:
	FloatingLeg() = default;
	~FloatingLeg() = default;
	double evaluate(MarketData marketData, const ICurrency& currency) const override;
};

